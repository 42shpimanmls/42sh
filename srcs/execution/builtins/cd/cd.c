#include "execution/builtins/builtins.h"
#include "variable.h"
#include <stdlib.h>
#include <unistd.h>
#include <libft.h>
#include "uint.h"
#include "errors.h"
#include <errno.h>
#include "utils.h"
#include "execution/builtins/cd.h"
#include <limits.h>

bool				last_is_slash(char const *str)
{
	if (str == NULL)
		return (false);
	return (str[ft_strlen(str) - 1] == '/');
}

static bool			first_comp_is_dot_or_dotdot(char const *str)
{
	if ((str[0] == '.' && (str[1] == '/' || str[1] == '\0'))
			|| (str[0] == '.' && str[1] == '.' && (str[2] == '/' || str[2] == '\0')))
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

static char			*parse_options(t_uchar *opt_addr, int argc, char **argv)
{
	char	*str;

	(void)argc;
	*opt_addr = '\0';
	if (*argv == NULL)
		return (NULL);
	argv++;
	while ((str = *argv) != NULL)
	{
		if (str[0] == '-' && (str[1] == 'L' || str[1] == 'P'))
			*opt_addr = str[1];
		else
			return ft_strdup(str);
		argv++;
	}
	return (NULL);
}

// set curpath to the string formed by the concatenation of the value of PWD, a <slash> character if the value of PWD did not end with a <slash> character, and curpath.
static void			set_curpath_from_pwd(char **str_addr)
{
	char	*path;

	if (str_addr == NULL || *str_addr == NULL)
		fatal_error("NULL ptr fed to set_curpath_from_pwd");
	if ((*str_addr)[0] == '/')
		return ;
	path = get_variable("PWD");
	if (!last_is_slash(path))
		path = ft_strjoinf(path, "/", 1);
	*str_addr = ft_strjoinf(path, *str_addr, 3);
}

/*
9. If curpath is longer than {PATH_MAX} bytes (including the terminating null)
and the directory operand was not longer than {PATH_MAX} bytes (including the
terminating null), then curpath shall be converted from an absolute pathname to
an equivalent relative pathname if possible. This conversion shall always be
considered possible if the value of PWD, with a trailing <slash> added if it
does not already have one, is an initial substring of curpath. Whether or not
it is considered possible under other circumstances is unspecified.
Implementations may also apply this conversion if curpath is not longer than
{PATH_MAX} bytes or the directory operand was longer than {PATH_MAX} bytes.
*/
void			save_the_day(char **curpath_addr, char const *directory, char const *pwd)
{
	char	*str;

	if (curpath_addr == NULL || *curpath_addr == NULL)
		fatal_error("NULL ptr fed to save_the_day");
	if (!(ft_strlen(*curpath_addr) + 1 > PATH_MAX && ft_strlen(directory) + 1 <= PATH_MAX))
		return ;
	if (!last_is_slash(pwd))
		str = ft_strjoin(pwd, "/");
	else
		str = ft_strdup(pwd);
	if (!ft_strstr(*curpath_addr, str))
		return ;
	strfreeswap(curpath_addr, ft_strdup((*curpath_addr) + ft_strlen(str)));
	free(str);
}

// 5. Starting with the first pathname in the <colon>-separated pathnames of CDPATH (see the ENVIRONMENT VARIABLES section) if the pathname is non-null, test if the concatenation of that pathname, a <slash> character if that pathname did not end with a <slash> character, and the directory operand names a directory. If the pathname is null, test if the concatenation of dot, a <slash> character, and the operand names a directory. In either case, if the resulting string names an existing directory, set curpath to that string and proceed to step 7. Otherwise, repeat this step with the next pathname in CDPATH until all pathnames have been tested.
static char			*test_cdpath(char const *dir, char const *path)
{
	char	*result;

	result = NULL;
	if (!(path == NULL || path[0] == '\0'))
	{
		// concatenation of that pathname, a <slash> character if that pathname did not end with a <slash> character, and the directory operand
		if (last_is_slash(path))
			result = ft_strdup(path);
		else
			result = ft_strjoin(path, "/");
		result = ft_strjoinf(result, dir, 1);
	}
	else
	{
		// concatenation of dot, a <slash> character, and the operand
		result = ft_strjoin("./", dir);
	}
	// test if (...) names a directory
	if (result != NULL && !is_directory(result))
		ft_strdel(&result);
	return (result);
}

static char			*find_cdpath(char const *directory)
{
	char	*cdpath;
	char	**slices;
	char	*str;
	size_t	u;

	cdpath = get_variable("CDPATH");
	if (cdpath == NULL)
		cdpath = ft_strdup("");
	slices = ft_strsplit(cdpath, ':');
	u = 0;
	str = NULL;
	while (u == 0 || slices[u] != NULL)
	{
		str = test_cdpath(directory, slices[u]);
		if (str != NULL)
			break ;
		if (u == 0 && slices[u] == NULL)
			break ;
		u++;
	}
	free(cdpath);
	ft_freetabchar(slices);
	return (str);
}

static BUILTIN_RET	cd_oldpwd()
{
	BUILTIN_RET	ret;
	char		*oldpwd;

	/*this shall be equivalent to the command:

	cd "$OLDPWD" && pwd*/
	oldpwd = get_variable("OLDPWD");
	if (oldpwd == NULL)
	{
		ft_putendl_fd("42sh: cd -: OLDPWD not set", 2);
		return (EXIT_FAILURE);
	}
	ret = builtin_cd(2, (char*[]){"cd", oldpwd, NULL});
	if (ret == EXIT_SUCCESS)
		ft_putendl(get_variable("PWD"));
	free(oldpwd);
	return (ret);
}

BUILTIN_RET 		builtin_cd(BUILTIN_ARGS)
{
	char	*directory;
	char	*curpath;
	char	*home;
	char	*new_pwd;
	char	*current_pwd;
	t_uchar	opt;
	int		ret;

	new_pwd = 0;
	/* If, during the execution of the above steps, the PWD environment variable is set, the OLDPWD environment variable shall also be set to the value of the old working directory (that is the current working directory immediately prior to the call to cd). */
	current_pwd = getcwd(NULL, 0);
	curpath = NULL;
	/* cd [-L|-P] [directory] */
	directory = parse_options(&opt, argc, argv);
	if (directory == NULL)
	{
		home = get_variable("HOME");
		if (home == NULL || home[0] == '\0')
		{
			/* 1. If no directory operand is given and the HOME environment variable is empty or undefined,
			the default behavior is implementation-defined and no further steps shall be taken. */
			ft_putendl_fd("42sh: cd: HOME not set", 2);
			ft_strdel(&current_pwd);
			return (EXIT_FAILURE);
		}
		else
		{
			/* 2. If no directory operand is given and the HOME environment variable is set to a non-empty value,
			the cd utility shall behave as if the directory named in the HOME environment variable was specified as
			the directory operand.*/
			directory = home;
		}
	}
	if (ft_strequ(directory, "-"))
	{
		free(directory);
		ft_strdel(&current_pwd);
		return (cd_oldpwd());
	}
	if (directory[0] == '/')
	{
		// 3. If the directory operand begins with a <slash> character, set curpath to the operand and proceed to step 7.
		curpath = ft_strdup(directory);
	}
	else
	{
		// 4. If the first component of the directory operand is dot or dot-dot, proceed to step 6.
		if (!first_comp_is_dot_or_dotdot(directory))
		{
			// 5. Starting with the first pathname in the <colon>-separated pathnames of CDPATH (see the ENVIRONMENT VARIABLES section) if the pathname is non-null, test if the concatenation of that pathname, a <slash> character if that pathname did not end with a <slash> character, and the directory operand names a directory. If the pathname is null, test if the concatenation of dot, a <slash> character, and the operand names a directory. In either case, if the resulting string names an existing directory, set curpath to that string and proceed to step 7. Otherwise, repeat this step with the next pathname in CDPATH until all pathnames have been tested.
			curpath = find_cdpath(directory);
		}
		// 6. Set curpath to the directory operand.
		if (curpath == NULL)
			curpath = ft_strdup(directory);
	}
	// 7. If the -P option is in effect, proceed to step 10. If curpath does not begin with a <slash> character, set curpath to the string formed by the concatenation of the value of PWD, a <slash> character if the value of PWD did not end with a <slash> character, and curpath.
	if (opt != 'P')
	{
		set_curpath_from_pwd(&curpath);
		// 8. The curpath value shall then be converted to canonical form as follows, considering each component from beginning to end, in sequence:
		strfreeswap(&curpath, canonicalize_path(curpath));
		// If, as a result of this canonicalization, the curpath variable is null, no further steps shall be taken.
		if (curpath == NULL)
		{
			free(directory);
			ft_strdel(&current_pwd);
			return (EXIT_SUCCESS);
		}
		new_pwd = ft_strdup(curpath);
		// 9. If curpath is longer than {PATH_MAX} bytes (including the terminating null) and the directory operand was not longer than {PATH_MAX} bytes (including the terminating null), then curpath shall be converted from an absolute pathname to an equivalent relative pathname if possible. This conversion shall always be considered possible if the value of PWD, with a trailing <slash> added if it does not already have one, is an initial substring of curpath. Whether or not it is considered possible under other circumstances is unspecified. Implementations may also apply this conversion if curpath is not longer than {PATH_MAX} bytes or the directory operand was longer than {PATH_MAX} bytes.
		save_the_day(&curpath, directory, current_pwd);
	}
	// 10. The cd utility shall then perform actions equivalent to the chdir() function called with curpath as the path argument. If these actions fail for any reason, the cd utility shall display an appropriate error message and the remainder of this step shall not be executed. If the -P option is not in effect, the PWD environment variable shall be set to the value that curpath had on entry to step 9 (i.e., before conversion to a relative pathname). If the -P option is in effect, the PWD environment variable shall be set to the string that would be output by pwd -P. If there is insufficient permission on the new directory, or on any parent of that directory, to determine the current working directory, the value of the PWD environment variable is unspecified.
	ret = chdir(curpath);
	if (ret == -1)
		print_errno_error(errno, "cd", curpath);
	else if (opt != 'P')
	{
		set_variable("OLDPWD", current_pwd, true);
		set_variable("PWD", new_pwd, true);
		ft_strdel(&new_pwd);
	}
	free(curpath);
	free(directory);
	ft_strdel(&current_pwd);
	if (ret != 0)
		ret = 2;
	return (ret);
}

/*
NAME

    cd - change the working directory

SYNOPSIS

    cd [-L|-P] [directory]

    cd -

DESCRIPTION

    The cd utility shall change the working directory of the current shell execution environment (see Shell Execution Environment) by executing the following steps in sequence. (In the following steps, the symbol curpath represents an intermediate value used to simplify the description of the algorithm used by cd. There is no requirement that curpath be made visible to the application.)

        1 If no directory operand is given and the HOME environment variable is empty or undefined, the default behavior is implementation-defined and no further steps shall be taken.

        2 If no directory operand is given and the HOME environment variable is set to a non-empty value, the cd utility shall behave as if the directory named in the HOME environment variable was specified as the directory operand.

        3 If the directory operand begins with a <slash> character, set curpath to the operand and proceed to step 7.

        4 If the first component of the directory operand is dot or dot-dot, proceed to step 6.

        5 Starting with the first pathname in the <colon>-separated pathnames of CDPATH (see the ENVIRONMENT VARIABLES section) if the pathname is non-null, test if the concatenation of that pathname, a <slash> character if that pathname did not end with a <slash> character, and the directory operand names a directory. If the pathname is null, test if the concatenation of dot, a <slash> character, and the operand names a directory. In either case, if the resulting string names an existing directory, set curpath to that string and proceed to step 7. Otherwise, repeat this step with the next pathname in CDPATH until all pathnames have been tested.

        6 Set curpath to the directory operand.

        7 If the -P option is in effect, proceed to step 10. If curpath does not begin with a <slash> character, set curpath to the string formed by the concatenation of the value of PWD, a <slash> character if the value of PWD did not end with a <slash> character, and curpath.

        8 The curpath value shall then be converted to canonical form as follows, considering each component from beginning to end, in sequence:

            a Dot components and any <slash> characters that separate them from the next component shall be deleted.

            b For each dot-dot component, if there is a preceding component and it is neither root nor dot-dot, then:

                i If the preceding component does not refer (in the context of pathname resolution with symbolic links followed) to a directory, then the cd utility shall display an appropriate error message and no further steps shall be taken.

                ii The preceding component, all <slash> characters separating the preceding component from dot-dot, dot-dot, and all <slash> characters separating dot-dot from the following component (if any) shall be deleted.

            c An implementation may further simplify curpath by removing any trailing <slash> characters that are not also leading <slash> characters, replacing multiple non-leading consecutive <slash> characters with a single <slash>, and replacing three or more leading <slash> characters with a single <slash>. If, as a result of this canonicalization, the curpath variable is null, no further steps shall be taken.

        9 If curpath is longer than {PATH_MAX} bytes (including the terminating null) and the directory operand was not longer than {PATH_MAX} bytes (including the terminating null), then curpath shall be converted from an absolute pathname to an equivalent relative pathname if possible. This conversion shall always be considered possible if the value of PWD, with a trailing <slash> added if it does not already have one, is an initial substring of curpath. Whether or not it is considered possible under other circumstances is unspecified. Implementations may also apply this conversion if curpath is not longer than {PATH_MAX} bytes or the directory operand was longer than {PATH_MAX} bytes.

        10 The cd utility shall then perform actions equivalent to the chdir() function called with curpath as the path argument. If these actions fail for any reason, the cd utility shall display an appropriate error message and the remainder of this step shall not be executed. If the -P option is not in effect, the PWD environment variable shall be set to the value that curpath had on entry to step 9 (i.e., before conversion to a relative pathname). If the -P option is in effect, the PWD environment variable shall be set to the string that would be output by pwd -P. If there is insufficient permission on the new directory, or on any parent of that directory, to determine the current working directory, the value of the PWD environment variable is unspecified.

    If, during the execution of the above steps, the PWD environment variable is set, the OLDPWD environment variable shall also be set to the value of the old working directory (that is the current working directory immediately prior to the call to cd).

OPTIONS

    The cd utility shall conform to XBD Utility Syntax Guidelines .

    The following options shall be supported by the implementation:

    -L
        Handle the operand dot-dot logically; symbolic link components shall not be resolved before dot-dot components are processed (see steps 8. and 9. in the DESCRIPTION).
    -P
        Handle the operand dot-dot physically; symbolic link components shall be resolved before dot-dot components are processed (see step 7. in the DESCRIPTION).

    If both -L and -P options are specified, the last of these options shall be used and all others ignored. If neither -L nor -P is specified, the operand shall be handled dot-dot logically; see the DESCRIPTION.

OPERANDS

    The following operands shall be supported:

    directory
        An absolute or relative pathname of the directory that shall become the new working directory. The interpretation of a relative pathname by cd depends on the -L option and the CDPATH and PWD environment variables. If directory is an empty string, the results are unspecified.
    -
        When a <hyphen-minus> is used as the operand, this shall be equivalent to the command:

        cd "$OLDPWD" && pwd

        which changes to the previous working directory and then writes its name.

STDIN

    Not used.

INPUT FILES

    None.

ENVIRONMENT VARIABLES

    The following environment variables shall affect the execution of cd:

    CDPATH
        A <colon>-separated list of pathnames that refer to directories. The cd utility shall use this list in its attempt to change the directory, as described in the DESCRIPTION. An empty string in place of a directory pathname represents the current directory. If CDPATH is not set, it shall be treated as if it were an empty string.
    HOME
        The name of the directory, used when no directory operand is specified.
    LANG
        Provide a default value for the internationalization variables that are unset or null. (See XBD Internationalization Variables for the precedence of internationalization variables used to determine the values of locale categories.)
    LC_ALL
        If set to a non-empty string value, override the values of all the other internationalization variables.
    LC_CTYPE
        Determine the locale for the interpretation of sequences of bytes of text data as characters (for example, single-byte as opposed to multi-byte characters in arguments).
    LC_MESSAGES
        Determine the locale that should be used to affect the format and contents of diagnostic messages written to standard error.
    NLSPATH
        [XSI] [Option Start] Determine the location of message catalogs for the processing of LC_MESSAGES. [Option End]
    OLDPWD
        A pathname of the previous working directory, used by cd -.
    PWD
        This variable shall be set as specified in the DESCRIPTION. If an application sets or unsets the value of PWD, the behavior of cd is unspecified.

ASYNCHRONOUS EVENTS

    Default.

STDOUT

    If a non-empty directory name from CDPATH is used, or if cd - is used, an absolute pathname of the new working directory shall be written to the standard output as follows:

    "%s\n", <new directory>

    Otherwise, there shall be no output.

STDERR

    The standard error shall be used only for diagnostic messages.

OUTPUT FILES

    None.

EXTENDED DESCRIPTION

    None.

EXIT STATUS

    The following exit values shall be returned:

     0
        The directory was successfully changed.
    >0
        An error occurred.

CONSEQUENCES OF ERRORS

    The working directory shall remain unchanged.

*/
