# Chapter 3 - Looping and Branching

Book: Pro Bash Programming. Authors: Chris F. A. Johnson and Jayant Varma. 2nd Edition.

## Exit Status
We can test the success of a command directly using the shell keywords while, until, and if. The exit status is also stored in the special parameter $?, being 0 if the command executed successfully and a positive integer if the command failed for some reason.

## Testing an Expression
There are three ways to test an expression: the test command, [[, or ((.

### test
The test command evaluates many kinds of expressions, from file properties to integers to strings. For example:
`test 1 -eq 2` or `[ test 1 -ne 1 ]`.

#### **File Tests**
To test the state of a file, it can be done with:
- -e: true if exists
- -f: true if a regular file
- -d: true if a directory
- -h: true if a symbolic link
- -x: true if you can execute the file
- -s: true if the file exists and is not empty

#### **Integer Tests**
Comparisons between integers use the following operators:
- -eq: test equality between x and y
- -ne: test inequality between x and y
- -gt: test if x is greater than y
- -lt: test if x is less than y
- -ge: test if x is greater than or equal to y
- -le: test if x is less than or equal to y

#### **String Tests**
Strings are concatenations of zero or more characters and can include any character except NUL. Here is how you can test them:

- =: if they are the same
- !=: if they are not the same
- -z: if it is empty
- -n: if it is nonempty
- \\<: if a string is before in the alphabetical order than another string 
- \\>: if a string is last in the alphabetical order than another string

The tests can also be combined with the -a (logical AND) and -o (logical OR) operators.

### [[ ... ]]: Evaluate an Expression
`[[ ... ]]` works just like `test`, but it is not a builtin command and it is nonstandard, so it is better to not use it when `test` could perform the same function.

#### **Enhancements over Test**
The major enhancement of `[ ... ]` over the `test` command is its capability to compare strings with regular expressions patterns with the =~ operator.

```bash
string=whatever
[[ $string =~ h[aeiou] ]]
echo $? # prints 0 to the screen
[[ $string =~ h[sdfghjkl] ]]
echo $? # prints 1 to the screen
```

### (( ... )): Evaluate an Arithmetic Expression
The feature `(( arithmetic expression ))` is also nonstandard and returns false if the arithmetic expression evaluates to zero and true otherwise. The portable equivalent is in the form of: 
`test $(( a - 2 )) -ne 0`

Because `(( expression ))` is a shell syntax and not a builtin command, we can use the operators `>` and `<` and will not be interpreted as a redirection operator. 

## Conditional Execution

### if
The if structure in Bash is:
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

### Conditional Operators, && and ||
Conditional operators AND and OR are evaluated from left to right. The AND operator is executed if the previous command is successful. The OR operator is executed if the previous command fails.

For example, to check for a directory and `cd` into it if it exists, use this: `test -d "$directory" && cd "$directory"`. To change directory and exit with an error if `cd` fails, use: `cd "$HOME/bin" || exit 1`.

### case
A `case` statement compares a word (usually a variable) against one or more patterns and executes the commands associated with the pattern. Its structure in Bash is:

```bash
case WORD in
    PATTERN) COMMANDS ;;
    PATTERN) COMMANDS ;; ## optional
esac
```

#### **Examples of case functions**
- Does one string contain another?
```bash
case $1 in
    *"$2"*) true ;;
    *) false ;;
esac
```

- Is this a valid positive integer?
```bash
case $1 in
    *[!0-9]*) false;;
    *) true ;;
esac
```

- To check whether there are the correct numbers of arguments on the command line.
```bash
case $# in
    3) ;; ## We need 3 args, so do nothing
    *) printf "%s\n" "Please provide three names" >&2
    exit 1
    ;;
esac
```

## Looping
### while
The `while` structure in Bash is:
```bash
while <list>
do
    <list>
done
```

To run a `while` command a specific number of times:
```bash
n=1
while [ $n -le 10 ]
do
    echo "$n"
    n=$(( $n + 1 ))
done
```

To run an infinite loop, we can use the `true` command:
```bash
while true ## ':' can be used in place of true
do
    read x
done
```

A while loop can be used to read line by line from a file:
```bash
while IFS= read -r line
do
    # do something with "$line"
done < FILENAME? 
```

### until
`until` loops as long as the condition fails.

```bash
n=1
until [ $n -gt 10 ]
do
    echo "$n"
    n=$(( $n + 1 ))
done
```

### for
At the top of a `for` loop, a variable is given a value from a list of words.

```bash
for var in Canada USA Mexico
do
    printf "%s\n" "$var"
done
```

Bash also has a nonstandard form similar to that found in the C programming language.

```bash
for (( n=1; n<=10; ++n ))
do
    echo "$n"
done
```

## Exercises
1. Write a script that asks the user to enter a number between 20 and 30. If the user enters an invalid number or a non-number, ask again. Repeat until a satisfactory number is entered.
2. Write a script that prompts the user to enter the name of a file. Repeat until the user enters a file that exists.