#!/bin/zsh

makefile_header="# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mazimi <mazimi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/04 15:35:21 by mazimi            #+#    #+#              #
#    Updated: 2017/05/04 15:35:21 by mazimi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #\n"       

c_header="/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazimi <mazimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 15:35:21 by mazimi            #+#    #+#             */
/*   Updated: 2017/05/04 15:35:21 by mazimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */\n" 

add_42_headers() {
    cd srcs
    for file in $(find . -name "*.c"); do
      add_42_header "$file"
    done
    cd ../includes
    for file in $(find . -name "*.h"); do
      add_42_header "$file"
    done
    cd ..
    add_42_header "Makefile"
    git status
    git diff
    git add srcs includes Makefile
    git commit -m "[mod] add 42 headers on top of files."
}

add_42_header() {
    src_file=$1
    tmp="/tmp/42_header"
    if [ $src_file = "Makefile" ]; then
        echo $makefile_header > $tmp
    else
        echo $c_header > $tmp
    fi
    cat $src_file >> $tmp
    cp $tmp $src_file
}

add_42_headers
