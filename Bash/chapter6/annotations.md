# Chapter 6 - Shell Functions

Book: Pro Bash Programming. Authors: Chris F. A. Johnson and Jayant Varma. 2nd Edition.

A *shell function* is a compound command that has been given a name and can be used in the same way as any other command: its arguments are available in the positional parameters and sets a return code.

Unlike individual scripts, when a function is called, it is executed in the same process as the script that calls it, so all variables of the script are available to it and the changes made to them will be seen by the calling script, but you can make variables that can be accessed only to the functions.

Some of the advantages of the functions are that they can be reused in a single script, but they are also available to other scripts, they improve legibility. At the command line, functions can do things that an external script cannot.

## Definition Syntax

There are two ways to create a function in Bash:

`function name <compound command>` or `name() <compound commmand>`. It can be also created with an hybrid: `function name() <compound command>`.

You can see an example of a function in the isvalidip-func script.

## Compound Commands

A compound command is a list of enclosed in `( ... )` or `{ ... }`, expressions enclosed in `(( ... ))` or `[[ ... ]]`, or one of the block-level shell keywords (`case`, `for`, `select`, `while`, and `until`).

An example of a function without braces can be seen in the valint script. With parentheses, a function is executed in a subshell.

```
$ funky() ( name=nobody; echo "name = $name" )$ name=Rumpelstiltskin$ funkyname = nobody$ echo "name = $name"name = Rumpelstiltskin
```

## Getting Results

There are three ways to get results from a function: returning information from a range of return codes, by setting one or more variables, or by printing its results.

### Set Different Exit Codes

We can convert the `rangecheck` script from Chapter3 to a function with a couple of improvements, we can return different values if the number is too high and others if it is too low. It also accepts the range to be checked as arguments on the command line. See `rangecheck-func` script.

### Print the Result

A function’s purpose may be to print information, either to the terminal or to a file. See `uinfo-func` script.

### Place Results in One or More Variables

A good way to get the value of more than one variable is to store them in variables. See two examples in the `max3-func` script, one of them uses three variables and the other uses an array.

**Convention**: functions names with an underscore, in the beginning, set a variable rather than print the result. The variable is the name of the function converted to uppercase.

## Function Libraries

It’s useful to create files of nothing but functions. Sourcing one of these files defines a number of related functions that can be used in the current script.

### Using Functions from Libraries

To source them just do: `. date-funcs`. Get date-funcs from: http://cfaj.freeshell.org/shell/ssr/08-The-Dating-Game.shtml.

## Sample Script

See `sample` script.