<h1>Simple Shell</h1>
A Unix Shell is a command-line interpreter or shell that provides a command line user interface for Unix-like operating systems. The shell is both an interactive command language and a scripting language, and is used by the operating system to control the execution of the system using shell scripts.

<h2>Features of the simple shell</h2>
<ul>
<li>Display a prompt and wait for the user to type a command. A command line always ends with a new line.</li>
<li>The prompt is displayed again each time a command has been executed.</li>
<li>The command lines are simple, no semicolons, no pipes, no redirections or any other advanced features.</li>
<li>The command lines are made only of one word. No arguments will be passed to programs.</li>
<li>If an executable cannot be found, print an error message and display the prompt again.</li>
<li>Handle errors.</li>
<li>You have to handle the “end of file” condition (Ctrl+D)</li>
<li>Handle command lines with arguments</li>
</ul>

<h2>Compilation</h2>
<p>The shell will be compiled this following way:</p>
<code>gcc -Wall -Werror -Wextra -pedantic -std=gnu89 \*.c -o hsh</code>

<h2>Usage</h2>
<p>The shell should work like in interactive mode</p>
<code>$ ./hsh | /bin/ls | hsh main.c shell.c | ($) | exit</code>
<p>Also in non-interactive mode</p>
<code>
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
$ cat test_ls_2
/bin/ls
/bin/ls
$
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
$
</code>

<h2>Contributors</h2>
<ul>
<li>MBOUME NAMEGNI Frank Patrick</li>
<li>ZUNAÏD Ali</li>
</ul>
