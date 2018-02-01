# ECE180a-GroupProject
A bit more challenging, a bit more work, but a lot more rewarding!

## It's Chloe's World, We're Just Living In It

Chloe is the Director of Engineering at JobCo, a company that exists somewhere within a Universe full of possibility -- so much possibility in fact -- that anything that *can* happen, probably already has.  Chloe likes to believe that she has an open mind. But the trouble with having an open mind is that people will insist on coming along and trying to put things in it. So despite the fact that everyone knows they don't exist, several Zombies are tenured and working in the Marketing Department. 

Like so many startups, JobCo. has sadly discovered that customers arent't interested in buying their namesake product. So, as is common practice in Silicon Valley, JobCo has decided to pivot. They're going to build and sell a completely _new_ product. The JobCo CEO wants to demonstrate the new product at CES. In **FIVE** weeks.  As a result, you your team have been invited to submit your a version of the "The Product", described below. 

## May The Best Team Win

You and your team are expected to build a program that offers the functionality summarized below. 

### Feature 1 -- command processing

Your product will run as a command line application (no GUI). Like most command-line applications, users will provide commands to your program by providing command-line arguments. The general form of the commands will be:

```
appname command <optional args>
```

As shown above, "appname" is the name of your executable. "Command" is the name of the command your program is being asked to execute. "<optional args> is an optional list of arguments. Some commands require multiple arguments, while others require not at all. A complete list of commands and associated arguments is provided later in this document.
  
For example, your program must be able to respond to a command-line request to display the application version number. To show the version number, a user will initiate the following command:

```
appname -v 
```

In this example, the command name is "-v", a shorthand that is equivalent to "version". Your program would then respond by showing the current version and build information. (see more details below).


### Feature 2 -- storage engine

The whole point of this program is to manage a collection of resources in a single (binary) file. Similar to the way a .tar or a .zip file stores a collection of compressed files. Note: Compression is not a requirement of this assignment.  However, if your team is bold, and wants to really outperform in the area of storage efficiency, you may "choose" to apply lossless compression to certain data. Again, this is NOT a requirement, and is not recommended for people with heart conditions. :)

#### Basic Storage

Your "storage engine" will create and managed binary files, that are comprised of an arbitrary set of files that are added. Users may add text files, or binary files like images or videos. Your program will not be asked to any single file larger than 500k in size. 

#### Space Management

A key goal of your storage engine is to minimize the overall size of your storage file. Imagine that a user adds 3 large files:

|[FILE1][FILE2][FILE3]|

Then the user deletes the 2nd file. The result (in terms of storage), may look like this (dots indicate free space):

|[FILE1].......[FILE3]|


As you can see, your total file is 1/3 larger than it needs to be. In order to get maximum points for efficiency, your storage algorithm might choose to move the data from third file into the space previously occupied by the 2nd file, and then truncate the excess bytes from the file:

|[FILE1][FILE3]|

A reasonable solution to reduce overall storage space, is to manage your underlying storage space in "chunks" of a fixed size that can easily be moved within the larger storage file. If your program keeps track of which "chunks" are unused, you algorithm could automatically reclaim unused space, rather than just appending new content to the end of your file.

### Feature 3 -- searching for contents

(details TBD)

## The Commands

Your program must be able to respond to following commands:

### Create StorageFile
1. create (storagefile) -- create a new "empty" storage unit, with given filename

### Add file to StorageFile
2. add (storagefile) (filename) -- add the named file to storage unit

### Delete file from StorageFile
3. del (storagefile) (filename) -- delete a named file from storage

### List files in StorageFile
4. list (storagefile) (files) -- show all the files in storage; -l is an alias for list

### Find file within StorageFile
5. find (storagefile) (filename) -- show properties associated with named file

### Extract a file from StorageFile
6. extract (storagefile) (file)  -- emit a copy of the named file to the terminal

### Show program version
7. version (show version number and build date); -v is an alias for "version"

## The Requirements

1. Your solution must be built using C++, and all of the code must be your own, original code. 
2. You MAY use the C++ STL in your solution if you deem it appropriate to do so. No "3rd party" libraries may be used. 
3. Your solution must be a stand-alone application, capable of being run from the command line. 
4. You cannot use external applications or services to do the work; your application must implement all the functionality. 

## Submitting Your Solution

1. To enter the competition, your team must submit a working (makeable) solution on github, on or before the deadline.
2. Your team must submit a 1-3 page paper describing the technical design concepts you used in your solution.
3. Your team must submit a 1-page "Marketing Brochure" that describes your product, highlights your team, and offers reasons why your solution should be chosen over your competitors. Since this is a marketing document, your submission must be witty, exciting, interesting and compelling. 

## Choosing a Winner

The Zombies in Marketing are awaiting your submissions. Here's how they will score your work:

### 1. Working Application (45pts)

Vlad-the-Compiler will build your application, and test it using an automated suite of tests. Your solution will recieve 10pts for each completed functional test, so long as you complete all tasks withing the standard time window.

If your solution doesn't build at all, you will receive 0 points in this category.

### 2. Performance and Efficiency (30pts)

Your solution will be measured and stack ranked along the dimensions of total performance and memory efficiency. 

#### Performance 
- Solutions in the 1st quartile in performance will receive 10 points
- Solutions in the 2nd quartile in performance will receive 8 points
- Solutions in the 3rd quartile in performance will receive 6 points
- Solutions in the 4th quartile in performance will recieve 4 points

#### Memory Efficiency
- Solutions in the 1st quartile in memory efficiency will receive 10 points
- Solutions in the 2nd quartile in memory efficiency will receive 8 points
- Solutions in the 3rd quartile in memory efficiency will receive 6 points
- Solutions in the 4th quartile in memory efficiency will recieve 4 points

### 3. Technical Design Summary (1-3 pages) (20pts)

Technical design papers should describe the approach the technical team took in solving the problem.  We can read your code, so this paper should describe the design ideas, challenges, and outline your solutions. Teams who fail to submit this paper will receive 0 points in this category. And don't even think about making us grab our red correction pen.

### 4. That "Something" Extra... (5pts)

Style matters. Confidence matters too. So do bribes, but our CEO frowns on that, so they're out of bounds. Otherwise, show us some great team spirit. Show us a team who works well together. Show us rock solid code, contributed by everyone on your team.

### Summary Score

Your submission will recieve a maximum of 100 points, aggregated from the points you earn in each of the 5 categories.


## Prize? Did you say Prize?

Why yes, we did say "Prize". Prize. Prize. Prize. As in, you get something of value for winning this competition.







