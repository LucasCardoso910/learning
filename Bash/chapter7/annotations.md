# Chapter 7 - String Manipulation

Book: Pro Bash Programming. Authors: Chris F. A. Johnson and Jayant Varma. 2nd Edition.

## Concatenation
A common example (used in Chapter 1) adds a directory to the PATH variable: `PATH=$PATH:$HOME/bin`. It is also possible to use the += operator.

To compare the two ways to do concatenation, it is possible to run this oneliner: `var=; time for i in {1..1000}; do var=${var}foo; done; var=; time for i in {1..1000}; do var+=foo; done`. 

### Repeat Character to a Given Length
An example of concatenation is to build a string of N characters. It can be seen in the repeat script. Using this script, the board_message script was created with a border of the same character.

## Processing Character by Character
To get the first and last characters of a string:

```bash
$ var=strip
$ first=${var:0:1}
$ last=${var:${#var}-1:1}
$ printf "%s\n" "$first"
s
$ printf "%s\n" "$last"
p
```

To operate on each character of a string one at a time, use a `while` loop:

```bash
while [ -n "$var" ]
do
    char=${var:0:1} ## assigns the first letter in $var to $char
    # do something with "$char"
    var=${var#?} ## everything but the first character
done
```

### Reversal
You can use this logic to reverse the order of characters in a string. Each letter is tacked on to the end of a new variable, as seen in the revstr script.

## Case Conversion
The `tr` external command translates characters in its first argument to the corresponding character in its second argument:

```bash
$ echo abcdefgh | tr ceh CEH # c => C, e => E, h => H
abCdEfgH
$ echo abcdefgh | tr ceh HEC # c => H, e => E, h => C
abHdEfgC
$ echo touchdown | tr 'a-z' 'A-Z'
TOUCHDOWN
```

In the POSIX shell, short strings can be converted efficiently using parameter expansion and a function containing a case statement as a lookup table, just as can be seen in the _upr script and the upword script, that uses _upr to convert a whole string to uppercase.

## Comparing Contents Without Regard to Case
To accept a short string as lowercase or uppercase, it can be easily done with a case statement:

```bash
read ok
case $ok in
    y|Y) echo "Great!" ;;
    n|N) echo "Good-bye"
         exit 1
         ;;
    *) echo Invalid entry ;;
esac
```

With longer strings, a better solution is to convert the input to uppercase first and then compare its values, just like it can be seen in the following script:

```bash
_upword "$monthname"
case $_UPWORD in ## convert $monthname to number
    JAN*) month=1 ;;
    ## ... put the rest of the year here
    DEC*) month=12 ;;
    *) echo "Invalid month: $monthname" >&2 ;;
esac
```

## Check for Valid Variable Name
A variable must be composed only of letters, numbers, or underscores and can start only with letters or underscores. A script that checks if a given string is a valid variable name can be found in the validname script.

## Insert One String into Another
This function splits the container string in two: the left part of the new string and the right part and appends the given string in the middle, concatenating the three strings. It can be found in the insert_string script.

## Overlay
The technique is similar to inserting a string, but the right side of the string begins at the length of the overlay further along. It can be found in the overlay script.

## Trim Unwanted Characters
Variables often arrive with unwanted padding: usually spaces or leading zeroes. A script that removes these unwanted characters can be found in the trim script.

## Index
This function returns the position of one string inside another. It can be found in the index script. The month2number script uses this same logic to convert a month given by string into a number.

## Exercises
1. What is wrong with this code (besides the inefficiency noted at the beginning of the chapter)?
   ```bash
   if ! echo ${PATH} | grep -q /usr/games
      PATH=$PATH:/usr/games
   fi
   ```
2. Write a function called `to_lower` that does the opposite of the `to_upper` function in **Listing 7-4**.
3. Write a function, palindrome, which checks whether its command-line argument is a palindrome (that is, a word or phrase that is spelled the same backward and forward). Note that spaces and punctuation are ignored in the test. Exit successfully if it is a palindrome. Include an option to print a message as well as set the return code.
4. Write two functions, ltrim and rtrim, which trim characters in the same manner as trim but from only one side of the string, left and right, respectively.

### Answers
1. It is missing the `then` command after the logical evaluation in if.
2. ```bash
   to_lower()
   { #@ USAGE: to_lower STRING
      _LWR=${1,,}
   }
   ```
3. Answer found in the palindrome function.
4. Answer found in the trim script file.