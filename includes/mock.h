#ifndef MOCK_H
# define MOCK_H

# ifdef ENABLE_MOCK
#  define MOCKABLE __attribute__((weak))
# else
#  define MOCKABLE
# endif

#endif
