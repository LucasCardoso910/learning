# Chapter 1 - Hello, World: Your First Shell Program
Book: Pro Bash Programming. Authors: Chris F. A. Johnson and Jayant Varma. 2nd Edition.

## The File
### The Naming of Scripts
To choose a good file name, you should do it as shortly as you can. It usually is some sort of abreviation of the compound and descriptive name (just like cd for change directory, ls for list, etc).
"test" is not a good choice for a temporary file because there is already a file named test in the $PATH

### Selecting a Directory for the Script
A good path to insert your personal bash files is $HOME/bin. You should add this path to your PATH variable just like this:

`PATH=$PATH:$HOME/bin`

### Creating the File and Running the Script
For small files, you don't need to use a text editor, you can simply:

`echo echo Hello, World! > bin/hw`

to create a file that prints "Hello, World!" when executed.
You should give then permission to execute the file with:

`chmod +x bin/hw`

Now, to execute it, you just need to type "hw" in your terminal!

## Building a Better "Hello, World!"
For a better "Hello, World!" script you can add the proper documentation:
hashbang with the path of the interpreter (bash, in this case) that will be used.
Text fields with the following information about the file: title, date, author <email>, version, description and options.
A useful tip is to create a character code to add after the hash and indicate the type of comment being made. In the book, he used "#:" for this personal informations.

## Exercises
1. Write a script that creates a directory called bpl inside $HOME. Populate this directory with two subdirectories, "bin" and "scripts".
2. Write a script to create the "Hello, World!" script, hw, in $HOME/bpl/bin; make it executable; and then execute it.