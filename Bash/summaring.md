# Summary

Book: Pro Bash Programming. Authors: Chris F. A. Johnson and Jayant Varma. 2nd Edition.

## Chapter 1 - Hello, World: Your First Shell Program

### Bash Script Initial Template
Initial template for a Bash file:

```bash
#! /bin/bash
#: Title        : {title}
#: Date         : {date}
#: Author       : {author} <email>
#: Version      : 1.0
#: Description  : Description about what script does
#: Options      : None
```

### Commands
- type: displays information about a command
- source: executes a script in the current shell environment

### Concepts
- shebang or hash-bang: a hash and exclamation mark followed by the path to the interpreter that will execute the file

### Variables
- PWD: pathname of the shell's current working directory
- HOME: the pathname of the user's home directory
- PATH: colon-separated list of directories where the command files are stored

## Chapter 2 - Input, Output, and Throughput

### Parameter and Variables

#### Positional Parameters
Positional parameters are arguments present on the command line and they are referred by a number.

#### Special Parameters
- \* and @: expand to the value of all the positional parameters combined.
- #: expands to the number of parameters
- $: contains the process identification (PID) number of the current process
- !: PID of the last command executed in the background
- _ and ?: last argument and exit code of the last executed command, respectively.
- -: the flag option currently in effect
  
#### **Variables**
Variables are identified by a name.

### echo, and Why You Should Avoid It
Don't use `echo`.

### printf: Formatting and Printing Data

#### **Escape Sequences:**
- \a: Alert
- \b: Backspace
- \e: Escape character
- \f: Form feed
- \n: Newline
- \r: Carriage return
- \t: Horizontal tab
- \v: Vertical tab
- \\\\: Backslash
- \nnn: A character specified by one to three octal digits
- \xHH: A character specified by one or two hexadecimal digits

#### **Format Specifiers:**
- %s: prints a string
- %b: works just like %s, but escape sequences are translated
- %d: prints an integer
- %f: prints a decimal fraction or a floating-point number
- %e: prints floating-point numbers in scientific notation
- %x: prints an integer in hexadecimal with lowercase letters
- %X: prints an integer in hexadecimal with uppercase letters

#### **Width Specification:**
- %{number}s: will print the string flush right by the number amount of characters
- %{-number}s: will print the string flush left by the number amount of characters
- %0{number}d: will print the integer with how many leading zeroes as defined by the number
- %.{number}f: will set the precision of the floating-point number as the number.

### Redirection: >, >>, and <
- \>: the file is created if it doesn't exist. If it does exist, the file is truncated to zero length before anything is sent to it.
- \>>: doesn't truncate the destination file; it appends to it.
- <: redirects the file as stdin to the command.

### Pipelines
Pipelines connect the standard output of one command directly to the standard input of another. The pipe symbol (|) is used between the command

### Command Substitution
The output of a command can be stored in a variable using command substitution.

## Chapter 3 - Looping and Branching
### Testing an Expression

#### **test**

##### **File Tests**
- -e: true if exists
- -f: true if a regular file
- -d: true if a directory
- -h: true if a symbolic link
- -x: true if you can execute the file
- -s: true if the file exists and is not empty

##### **Integer Tests**
- -eq: test equality between x and y
- -ne: test inequality between x and y
- -gt: test if x is greater than y
- -lt: test if x is less than y
- -ge: test if x is greater than or equal to y
- -le: test if x is less than or equal to y

##### **String Tests**
- =: if they are the same
- !=: if they are not the same
- -z: if it is empty
- -n: if it is nonempty
- \\<: if a string is before in the alphabetical order than another string 
- \\>: if a string is last in the alphabetical order than another string

The tests can also be combined with the -a (logical AND) and -o (logical OR) operators.

#### **[[ ... ]]: Evaluate an Expression**
##### **Enhancements over Test**
The major enhancement of `[ ... ]` over the `test` command is its capability to compare strings with regular expressions patterns with the =~ operator.

#### **(( ... )): Evaluate an Arithmetic Expression**

### Conditional Execution
#### **if**
```bash
if <condition list 1>
then
    <command list 1>
elif <condition list 2>
then
    <command list 2>
else
    <command list 3>
fi
```

#### **case**

```bash
case WORD in
    PATTERN) COMMANDS ;;
    PATTERN) COMMANDS ;; ## optional
esac
```

### Looping
#### **while**
```bash
while <list>
do
    <list>
done
```

#### **until**
```bash
until <condition list>
do
    <command list>
done
```

#### **for**
```bash
for var in Canada USA Mexico
do
    printf "%s\n" "$var"
done
```

or

```bash
for (( n=1; n<=10; ++n ))
do
    echo "$n"
done
```

## Chapter 4 - Command-Line Parsing and Expansion

### Quoting
The quoting step in the Bash parsing is to separate words using unquoted whitespace.

### Brace expansion
It operates on unquoted braces containing either a comma-separated list or a sequence and every element becomes a separate argument.

### Tilde expansion
Any unquoted tilde will be expanded to the user's home directory.

### Parameter and variable expansion
The process of parameter expansion replaces a variable with its contents.

### Arithmetic expansion
When the shell encounters `$(( expression ))`, it evaluates expression and places the result on the command line.

### Command substitution
Command substitution replaces a command with its output. The command must be placed either between backticks (\` `command` \`) or between parentheses preceded by a dollar sign (`$( command )`). 

### Word splitting
Word splitting is based on the value of the Internal Field Separator variable, IFS. IFS value can be altered and it will change the characters that delimit what are the words.

### Pathname expansion
Unquoted words on the command line containing the characters \*, ? and [ are treated as *file globbin patterns*, and are replaced by an alphabetical list of files that match the pattern.

### Process substitution
Process substitution creates a temporary filename for a command or list of commands. You can use it anywhere a file name is expected. The form `<(command)` makes the output of `command` available as a file name; `>(command)` is a file name that can be written to.

## Parsing Options
The options to a shell script, single characters preceded by a hyphen, can be parsed with the built-in command `getopts`.

## Chapter 5 - Parameters and Variables
### The Scope of a Variable: Can You See It from Here?
By default, a variable's definition is known only to the shell in which it is defined. To export a variable to the environment, it is used the shell builtin command export: `export var=whatever` or just `export var`

### Parameter Expansion
#### **Bourne Shell**
- `${var:-default}` use default value if var is unset or empty
- `${var-default}` use default value if var is unset
- `${var:+alternate}` use alternate value if var is set and not empty
- `${var+alternate}` use alternate value if var is set, even if empty
- `${var:?message}` displays message and exit if var is empty or unset
- `${var?message}` displays message and exit if var is unset

#### **POSIX Shell**
- `${#var}` returns the length of the expanded value of var
- `${var%PATTERN}` removes the shortest match from the end
- `${var%%PATTERN}` removes the longest match from the end
- `${var#PATTERN}` removes the shortest match from the beginning
- `${var##PATTERN}` removes the longest match from the beginning

#### **Bash**
- `${var/PATTERN/STRING}` replace the first instance of pattern with STRING
- `${var//PATTERN/STRING}` replace all instances of pattern with string
- `${var:OFFSET}` return a substring of $var starting at OFFSET
- `${var:OFFSET:LENGTH}` return a substring of $var of LENGTH size starting at OFFSET
- `${!var}` access a variable contained in another variable (indirect reference).

#### **Bash-4.0**
- `${var^PATTERN}` converts to uppercase the first character in var if it matches PATTERN.
- `${var^^PATTERN}` converts to uppercase all characters in var that matches PATTERN.
- `${var,PATTERN}` converts to lowercase the first character in var if it matches PATTERN.
- `${var,,PATTERN}` converts to lowercase all characters in var that matches PATTERN.

### Arrays
#### **Displaying Arrays**
Array elements are referenced by the name and a subscript in braces. It can be used * or @ to access all elements.

#### **Assigning Array Elements**
Elements can be assigned using an index.

`name[42]=Adams`

`a[${#a[@]}]="$RANDOM"`

`province=( Quebec Ontario Manitoba )`

`province+=( Alberta )`

#### **Associative Arrays**
To create a new array: `declare -A array`. And to operate it: `array[a]="a $RANDOM"`.

## Chapter 6 - Shell Functions
A shell function is a compound command that has been given a name and can be used in the same way as any other command. All variables of the script are available to the function.

### Definition Syntax
`function name <compound command>`

`name() <compound command>`

`function name() <compound command>`

### Compound Commands
A compound command is a list of enclosed in `( ... )` or `{ ... }`, expressions enclosed in `(( ... ))` or `[[ ... ]]`, or one of the block-level shell keywords (`case`, `for`, `select`, `while`, and `until`).

### Gettin Results
There are three ways to get a result from a function:
- Set Different Exit Codes
- Print the Result
- Place Results in One or More Variables

## Functions Libraries
A function library is a script with functions, it can be sourced with the command `. func-file.sh`.

## Chapter 7 - String Manipulation
### Concatenation
It can be done with `foo=$foo$bar` or with `foo+=$bar`.

#### Repeat Character to a Given Length
This process uses concatenation inside a loop a certain number of times.

### Processing Character by Character
Given a string in a var variable:

```bash
first_character=${var:0:1}
last_character=${var:${#var}-1:1}

## Operate on each character of a string one character at a time
while [ -n "$var" ]
do
    char=${var:0:1}
    # do something with char
    var=${var#?}
done
```

### Case Conversion
```bash
$ echo abcdefgh | tr ceh CEH
abCdEfgH
$ echo touchdown | tr 'a-z' 'A-Z'
TOUCHDOWN
```

### Comparing Contents Without Regard to Case
Just convert the string to uppercase and then compare the desired uppercase strings to it.

### Interesting scripts in this chapter
- revstr
- _upr
- validname
- insert_string
- overlay
- trim
- index
- month2number
