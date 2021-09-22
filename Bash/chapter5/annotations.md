# Chapter 5 - Parameters and Variables

Book: Pro Bash Programming. Authors: Chris F. A. Johnson and Jayant Varma. 2nd Edition.

## The Naming of Variables 
Variables names can contain only letters, numbers, and underscores, and they must start with a letter or an underscore. The best tip in the naming of a variable is to choose a name that gives a real indication of what the variable contains.

Convention says that environment variables should be in capital letters, while local variables should be in lowercase. As Bash has more than 80 uppercase variables internally, it is a good idea to use an underscore at the beginning of one you create.

There are two main naming schemes: capitalizing all first letters in a word in the variable and using all lowercase letters (underscores in the between if it gets confusing).

Single-letter names should be used rarely. They are appropriate as the index in a loop or as a variable name when reading throwaway material from a file.

## The Scope of a Variable: Can You See It from Here?
By default, a variable's definition is known only to the shell in which it is defined (and its subshells). A script called by the current script will only know about the variable if it is exported to the *environment*, an array of strings of the form name=value that is passed to every external command.

To export a variable to the environment, it is used the shell builtin command export: `export var=whatever` or just `export var`, if it has been declared before. **Note**: Exporting a variable doesn't make it visible anywhere except child processes and variables set in a subshell are not visible to the script that called it.

Bugs in a Bash script sometimes happens for the command being executed in a subshell and, therefore, the variable not being in the script scope. To help prevent this, bash-4.2 inserted a new option, `lastpipe`, that enables the last process in a pipeline to be executed in the current shell: `shopt -s lastpipe`.

## Shell Variables
There are three main classifications of shell variables: the ones that are used by bash internally, the ones that are used in debugging, and the ones that are in common use in shell programs.

| Variables | set | by | shell |
|:---------:|:---:|:--:|:-----:|
|BASH|BASHOPTS|BASHPID|BASH_ALIASES|
|BASH_ARGC|BASH_ARGV|BASH_CMDS|BASH_COMMAND|
|BASH_EXECUTION_STRING|BASH_LINENO|BASH_REMATCH|BASH_SOURCE|  
|BASH_SUBSHELL|BASH_VERSINFO|BASH_VERSION|BASH_CWORD|
|COMP_KEY|COMP_LINE|COMP_POINT|COMP_TYPE|
|COMP_WORDBREAKS|COMP_WORDS|COPROC|DIRSTACK|
|EUID|FUNCNAME|GROUPS|HISTCMD|
|HOSTNAME|HOSTTYPE|LINENO|MACHTYPE|
|MAPFILE|OLDPWD|OPTARG|OPTIND|
|OSTYPE|PIPESTATUS|PPID|PWD|
|RANDOM|READLINE_LINE|READLINE_POINT|REPLY|
|SECONDS|SHELLOPTS|SHLVL|UID|

| Variables | used | by | shell |
|:---------:|:----:|:--:|:-----:|
|BASH_COMPAT|BASH_ENV|BASH_XTRACEFD|CDPATH|
|CHILD_MAX|COLUMNS|COMPREPLY|EMACS|
|FCEDIT|FIGNORE|FUNCNEST|GLOBIGNORE|
|HISTCONTROL|HISTFILE|HISTFILESIZE|HISTIGNORE|
|HISTSIZE|HISTTIMEFORMAT|HOME|HOSTFILE|
|IFS|IGNOREEOF|INPUTRC|LANG|
|LC_ALL|LC_COLLATE|LC_CTYPE|LC_MESSAGES|
|LC_NUMERIC|LC_NUMERIC|LINES|MAIL|
|MAILCHECK|MAILPATH|OPTERR|PATH|
| POSIXLY_CORRECT |PROMPT_COMMAND|PROMPT_DIRTRIM|PS1|
|PS2|PS3|PS4|SHELL|
|TIMEFORMAT|TMOUT|TMPDIR|auto_resume|

## Parameter Expansion

### Bourne Shell
The Bourne shell and its successors have expansions to replace an empty or unset variable with a default, to assign a default value to a variable if it is empty or unset, and to halt execution and print an error message if a variable is empty or unset.

#### **${var:-default} and ${var-default}: Use Default Values**
`${var:-default}` checks to see wheter a variable is unset or empty and exapnds to a default string if it is.
If the colon is omitted (`${var-default}`), the expansion checks only whether the variable is unset.

#### **${var:+alternate}, ${var+alternate}: Use Alternate Values**
`${var:+alternate}` checks to see wheter a variable is set and not empty, assigning the alternate value to var if so.
If the colon is omitted (`${var+alternate`), alternate is used if the variable is set, even if it is empty.

#### **${var:=default}, ${var=default}: Assign Default Values**
`${var:=default} ` works the same way as `${var:-default}`, but also assigns the default value to the variable.

#### **${var:?message}, ${var?message}: Display Error Message If Empty or Unset**
`${var:?message}` checks if var is empty or unset and if so, displays the message and exit with status of 1. `${var?message}` checks only if var is unset, it displays nothing if var is just empty.

### POSIX Shell
#### **${#var}: Length of Variable's Contents**
This expansion returns the length of the expanded value of the variable.

#### **${var%PATTERN}: Remove the Shortest Match from the End**
The variable is expanded, and the shortest string that matches PATTERN is removed from the end of the expanded value.

```bash
var=Toronto
var=${var%o*}
printf "%s\n" "$var"
```
`Toront`

#### **${var%%PATTERN}: Remove the Longest Match from the End**
The variable is expanded and the longest string that matches PATTERN from the end of the expanded value is removed.

```bash
var=Toronto
var=${var%%o*}
printf "%s\n" "$var"
```
`T`

#### **${var#PATTERN}: Remove the Shortest Match from the Beginning**
The variable is expanded, and the shortest string that matches PATTERN is removed from the beginning of the expanded value:

```bash
var=Toronto
var=${var#*o}
printf "%s\n" "$var"
```
`ronto`

#### **${var##PATTERN}: Remove the Longest Match from the Beginning**
The variable is expanded, and the longest string that matches PATTERN is removed from the beginning of the expanded value.

```bash
scriptname=${0##*/}
printf "%s\n" "$scriptname"
```
`/home/lucascardoso910/bin/script`

### Bash
#### **${var//PATTERN/STRING}: Replace All Instances of PATTERN with STRING**
Because the question mark matches any single character, this example hides a password:

```bash
$ passwd=zxQ1.=+-a
$ printf "%s\n" "${passwd//?/*}"
*********
```

With a single slash, only the first matching characters are replaced.

```bash
$ printf "%s\n" "${passwd/[[:punct:]]}"
zxQ1*=+-a
```

#### **${var:OFFSET:LENGTH}: Return a Substring of $var**
A Substring of $var starting at OFFSET is returned. If LENGTH is specified, that number of characters is substituted; otherwise, the rest of the string is returned.

```bash
$ var=Toronto
$ printf "%s\n" "${var:3:2}"
on
$ printf "%s\n" "${var:3}"
onto
$ printf "%s\n" "${var:-3}"
:nto:
```

#### **${!var}: Indirect Reference**
If you have one variable containing the name of another, for example, `x=yes` and `a=x`, bash can use an indirect reference:

```bash
$ x=yes
$ a=x
$ printf "%s\n" "${!a}"
yes
```

The same effect can be had using the `eval` built-in command.

```bash
$ eval "printf \"%s\n\" \"\$$a\""
yes
```

### Bash-4.0
#### **${var^PATTERN}: Convert to Uppercase**
The first character of var is converted to uppercase if it matches PATTERN, with a double caret (^^), it converts all characters matching PATTERN. If PATTERN is omitted, all characters are matched.

#### **${var,PATTERN}: Convert to Lowercase**
This expansion works in the same way as the previous one, except that it converts uppercase to lowercase.

## Positional Parameters
To use each parameter in turn, there are two common methods.

```bash
for param in "$@" ## or just: for param
do
    ## do something with $param
done
```

or

```bash
while (( $# ))
do
    ## do something with $1
    shift
done
```

## Arrays
### Integer-Indexed Arrays
The individual members of an array variable are assigned and accessed with a subscript of the form [N]. The first element has an index of 0. In bash, arrays are sparse, they needn't be assigned with consecutive indices. An array can have an element with an index of 0, another with an index of 42, and no intervening elements.

### Displaying Arrays
Array elements are referenced by the name and a subscript in braces.
```bash
$ printf "%s\n" "${BASH_VERSINFO[0]}"
5
$ printf "%s\n" "${BASH_VERSINFO[1]}"
0
```

All the elements of an array can be printed with a single statement. * expands to a single parameter if quoted and using @ each element expands to a separate argument.

```bash
$ printf "%s\n" "${BASH_VERSINFO[*]}"
5 0 17 1 release x86_64-pc-linux-gnu
$ printf "%s\n" "${BASH_VERSINFO[@]}"
5
0
17
1
release
x86_64-pc-linux-gnu
```

Various parameter expansions work on arrays:

```bash
$ printf "%s\n" "${BASH_VERSINFO[@]:1:2}" ## minor version number and patch level
0
17
```

The length expansion returns the number of elements in the array when the subscript is * or @.

```bash
$ printf "%s\n" "${#BASH_VERSINFO[*]}"
6
$ printf "%s\n" "${#BASH_VERSINFO[2]}" "${#BASH_VERSINFO[5]}"
2
19
```

### Assigning Array Elements
Elements can be assigned using an index; the following commands create a sparse array:

```bash
name[0]=Aaron
name[42]=Adams
```

Arrays are more useful when elements are assigned consecutively, it can be done:
```bash
$ unset a
$ a[${#a[@]}]="1 $RANDOM" ## ${#a[@]} is 0
$ a[${#a[@]}]="2 $RANDOM" ## ${#a[@]} is 1
$ printf "%s\n" "${a[@]}"
1 8218
2 14564
```

An entire array can be populated with a single command:
```bash
$ province=( Quebec Ontario Manitoba )
$ printf "%s\n" "${province[@]}"
Quebec
Ontario
Manitoba
```

The += operator can be used to append values to the end of an indexed array:
```bash
province+=( Saskatchewan )
province+=( Alberta "Britsh Columbia" "Nova Scotia" )
printf "%-25s %-25s %s\n" "${province[@]}"
Quebec                    Ontario                   Manitoba
Saskatchewan              Alberta                   Britsh Columbia
Nova Scotia
```

### Associative Arrays
Associative arrays use strings as subscripts and must be declared before being used.
```bash
$ declare -A array
$ for subscript in a b c d e
> do
>     array[$subscript]="$subscript $RANDOM"
> done
$ printf ":%s:\n" "${array[@]}" ## print the entire array
:a 13856:
:b 6235:
:c 1574:
:d 14020:
:e 9165:
```
## Exercises
1. By default, where can a variable assigned in a script be accessed? Select all that apply:
   - In the current script
   - In functions defined in the current script
   - In the script that called the current script
   - In scripts called by the current script
   - In subshells of the current script
2. I advise against using single-letter variables names but give a couple of places where they are reasonable. Can you think of any other legitimate uses for them?
3. Given `var=192.168.0.123`, write a script that uses parameter expansion to extract the second number, `168`.

### Answers
1. - [x] In the current script
   - [x] In functions defined in the current script
   - [ ] In the script that called the current script
   - [ ] In scripts called by the current script
   - [x] In subshells of the current script
2. 
3. ```bash
   #! /bin/bash

   var=192.168.0.123
   var=${var#*.}
   var=${var%%.*}
   echo $var
   ```
