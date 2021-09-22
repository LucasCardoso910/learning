# Chapter 4 - Command-Line Parsing and Expansion

Book: Pro Bash Programming. Authors: Chris F. A. Johnson and Jayant Varma. 2nd Edition.

When a line is executed, Bash first splits it into words wherever there is unquoted whitespace and then performs up to eight types of expansion on them as appropriate:

- Brace expansion
- Tilde expansion
- Parameter and variable expansion
- Arithmetic expansion
- Command substitution
- Word splitting
- Pathname expansion
- Process substitution

## Quoting
The first step in the parsing process of the bash shell is to separate words using unquoted whitespace, that is, spaces, tabs and newlines that are not within quotes or espace characters.

The difference, in Bash, between single and double quotes is that single quotes taken every character literally, so it cannot contain a single quote inside of it, since the escape character \ will be taken as a literal. To include single quotes inside of a single quote sentence, it is needed to use the format `$'string'`.

Using the `sa` script, we can have:

`sa \ this "is a" 'demonstration of' \  '"quoted"' quotes\ and\ escapes`

which returns:

```
: this:
:is a:
:demonstration of:
: :
:"quoted":
:quotes and escapes:
```

## Brace Expansion
The first expansion to be performed is the brace expansion: it operates on unquoted braces containing either a comma-separated list or a sequence and every element becomes a separate argument.

Let's see some examples:
- `sa {one,two,three}`

```
:one:
:two:
:three:
```

- `sa {1..3}`

```
:1:
:2:
:3:
```

- `sa {a..c}`

```
:a:
:b:
:c:
```

- `sa pre{d,l}ate`

```
:predate:
:prelate:
```

- `sa {{1..3},{a..c}}`

```
:1:
:2:
:3:
:a:
:b:
:c:
```

- `sa {1..3}{a..c}`

```
:1a:
:1b:
:1c:
:2a:
:2b:
:2c:
:3a:
:3b:
:3c:
```

- `sa {01..13..3}`

```
:01:
:04:
:07:
:10:
:13:
```

- `sa {a..h..3}`

```
:a:
:d:
:g:
```

## Tilde Expansion
Any unquoted tilde will be expanded to the user's home directory. For example, in my case, it is:
`sa ~` and becomes `:/home/lucascardoso910`. 

It can also be used with a login name:

`sa ~root ~lucascardoso910`
```
:/root:
:/home/lucascardoso910:
```

## Parameter and Variable Expansion
The process of parameter expansion replaces a variable with its contents; it is introduced by a dollar sign ($).

```bash
var=whatever
sa "$var"
```
`:whatever:`

Parameters may be enclosed in braces, but they are required only in a few cases: when referring to a positional parameter grater than nine or when a variable name is followed immediately by a character that could be part of a name:

```bash
first=Jane
last=Johnson
sa "$first_$last" "${first}_$last"
```

```
:Johnson:
:Jane_Johnson:
```

## Arithmetic Expansion
When the shell encounters `$(( expression ))`, it evaluates expression and places the result on the command line. Inside it, we can use basic arithmetic operations signs and logical operators, muck like the C programming language.

## Command Substitution
Command substitution replaces a command with its output. The command must be placed either between backsticks (\` `command` \`) or between parentheses preceded by a dollar sign (`$( command )`). 

## Word Splitting
The results of parameter and arithmetic expansions, as well as command substitution, are subjected to word splitting if they were not quoted.

Word splitting is based on the value of the Internal Field Separator variable, IFS. IFS value can be altered and it will change the characters that delimit what are the words.

## Pathname Expansion
Unquoted words on the command line containing the characters \*, ? and [ are treated as *file globbin patterns*, and are replaced by an alphabetical list of files that match the pattern.

- \*: matches all patterns
- ?: matches any single character
- [: matches any one of the enclosed characters
- [[:lower:]]: matches all lowercase letters

It is possible to disable filename expansion with the `set -f` command.

## Process Substitution
Process substitution creates a temporary filename for a command or list of commands. You can use it anywhere a file name is expected. The form `<(command)` makes the output of `command` available as a file name; `>(command)` is a file name that can be written to.

`sa <(ls -l) >(pr -Tn)`

## Parsing Options
The options to a shell script, single characters preceded by a hyphen, can be parsed with the builtin command `getopts`.

## Summary

### Commands
- `head`: Extracts the first N lines from a file; N defaults to 10
- `cut`: Extracts columns from a file

## Exercises
1. How many arguments are there on this command line?
   
```bash
sa $# $(date "+%Y %m %d") John\ Doe
```

**Answer**: This command line presents 5 arguments: the number in the $# variable, the year, the month, the day, and the string of the name "John Doe".

2. What potential problem exists with the following snippet?

```bash
year=$( date +%Y )
month=$( date +%m )
day=$( date +%d )
hour=$( date +%H )
minute=$( date +%M )
second=$( date +%S )
```