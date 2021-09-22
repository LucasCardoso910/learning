# Chapter 2 - Input, Output and Throughput

Book: Pro Bash Programming. Authors: Chris F. A. Johnson and Jayant Varma. 2nd Edition.

## Parameter and Variables

A parameter is an entity that stores values. Its values are accessed with the dollar sign $. In Bash, there are three kinds of parameters:

### Positional Parameters

Positional parameters are arguments present on the command line and they are referred by a number.

Bourne Shell could only address up to nine positional parameters, for retro compatibility reasons, to access a number bigger than 9 in Bash, you need to use braces, like this: `${15}`.

The function `shift N` (default value of N is 1), moves the positional parameters by N moves. Running `shift` turns $1 into $0, for example.

 ### Special Parameters 

Special parameters are set by the shell to store information about aspects of its current state. Their name is nonalphanumeric characters. They are:

- \* and @: expand to the value of all the positional parameters combined.
- #: expands to the number of parameters
- $: contains the process identification (PID) number of the current process
- !: PID of the last command executed in the background
- _ and ?: last argument and exit code of the last executed command, respectively.
- -: the flag option currently in effect

 ### Variables 

Variables are identified by a name. A name is a word that contains only letters, numbers, or underscore and cannot begin with a number.

To assign a value to a variable, do this:

`variable=VALUE`

 ## Arguments and Options 

Arguments are words entered after the command. They are separated by unquoted and unescaped whitespace.

Options are arguments that are traditionally preceded by a single hyphen if they are just one letter or by a double hyphen if they are a long option.

 ## echo, and Why You Should Avoid It 

Basically, there is a shell option (xpg\_echo) that makes echo behave like an older version, so, for security purposes, it is better to avoid using echo and, instead, use printf.

 ## printf: Formatting and Printing Data 

The Bash function printf is based on the same name function from C.

 ### Escape Sequences: 

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

 ### Format Specifiers: 

Works just like in C. The most common specifiers are:

- %s: prints a string
- %b: works just like %s, but escape sequences are translated
- %d: prints an integer
- %f: prints a decimal fraction or a floating-point number
- %e: prints floating-point numbers in scientific notation
- %x: prints an integer in hexadecimal with lowercase letters
- %X: prints an integer in hexadecimal with uppercase letters

 ### Width Specification: 

We can specify a certain width using a number next to the percent sign.

- %{number}s: will print the string flush right by the number amount of characters
- %{-number}s: will print the string flush left by the number amount of characters
- %0{number}d: will print the integer with how many leading zeroes as defined by the number
- %.{number}f: will set the precision of the floating-point number as the number.

 ### Printing to a Variable 

Bash has a -v option to store the output in a variable instead of printing to the standard output.

 ## Standard Input/Output Streams and Redirection 

On Unix, everything is a stream of bytes, accessible as files. There are three streams that are rarely accessed by a filename: standard input, standard output, and standard error. Otherwise, these streams are referred to by numbers or by their contracted names:

- Standard input: represented by number 0 and by stdin
- Standard output: represented by the number 1 and by stdout
- Standard error: represented by the number 2 and by stderr

 ### Redirection: >, >>, and < 

I/O streams can be redirected to (or from) a file or into a pipeline.

When redirecting using >, the file is created if it doesn't exist. If it does exist, the file is truncated to zero length before anything is sent to it.

The >> operator doesn't truncate the destination file; it appends to it. Pay attention that redirecting standard output does not redirect standard error. Error messages will still be displayed on the monitor.

To redirect the standard error, it is needed to use the file descriptor (FD) 2:

`printf '%s\n%v\n' OK? Oops! > FILE 2 > ERRORFILE`

This line sends standard output to FILE and standard error to ERRORFILE. It can be also sent to /dev/null, where anything written to it is discarded:

`printf '%s\n%v\n' OK? Oops! 2>/dev/null`

And it can be also redirected to another I/O stream using >&N, where N is the number of the file descriptor:

`printf '%s\n%v\n' OK? Oops! > FILE 2>&1`

At least, a command that reads from standard input can have its input redirected from a file:

`tr, H wY < bin/hw`

It is possible to use the `exec` command to redirect the I/O streams for the rest of the script or until it's changed again.

`exec 1>tempfile`

`exec 0<datafile`

`exec 2>errorfile`

 ## Pipelines 

Pipelines connect the standard output of one command directly to the standard input of another. The pipe symbol (|) is used between the commands:

`printf "%s\n" "$RANDOM" "$RANDOM" "$RANDOM" "$RANDOM" | tee FILENAME`

The `tee` command reads from stdin and passes to one or more files as well as to stdout. `$RANDOM` returns a random integer between 0 and 23,767.

 ## Command Substitution 

The output of a command can be stored in a variable using command substitution. Just do like this: `date=$( date )`.

 ## Exercises 

1. What is wrong with this command?

```bash
tr A Z < $HOME/temp > $HOME/temp
```

- ***Answer***: As the redirecting is made before the execution of the command, in this case, it will first overwrite the file with an empty string and then use this empty file as input for the command, meaning that it will never have real input.

2. Write a script, using `$RANDOM`, to write the following output both to a file and to a variable. The following numbers are only to show the format; your script should produce different numbers:

```bash
1988,2365
13798,14178
10081,134
3816,15098
```