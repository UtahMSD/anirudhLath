# Lab 4: SQL

In this lab, you will practice creating SQL queries to: retrieve useful data from a database, create tables in a database, and populate tables with data.

For all SQL queries, do not "query by instance" - in other words, don't hard-code your queries to only work for the instance data currently in the tables. Your queries must work even if the instance data changes.

For the parts where you perform queries, write the queries in a markdown file and commit that to Github so we can see what you came up.  

## Part 1 - SQL Command Line

You can use any SQL client you are familiar with, but we can not guarantee we will be able to help you with anything other than the Linux `mysql` command-line client. Due to firewalls, you'll probably need to be logged into a CADE machine to connect to our databse server (maybe it will work on campus, or using an on-campus VPN, but I'm not sure). 

### Remote Linux login

By now, you should know how to log into a Linux machine remotely. See [this page for a refresher](../cadeInfo.md).

Log into a CADE Linux machine such as lab1-x or lab2-x using `ssh`. Once you have your remote shell, you can run `mysql`:

```
mysql -h atr.eng.utah.edu -u <uid> -p
```

-h specifies which host (server) to connect to. Our server is `atr.eng.utah.edu`

-u specifies your username. Replace <uid> with your uid. This is a lowercase 'u' followed by 7 digits.

-p specifies that it will ask for your password. Your default password is "changeme".

### Change your password

After you login, and before you do anything else, run the following SQL command to change your password:

```
SET PASSWORD FOR "username" =  PASSWORD("newpassword");
```

Where username is replaced with your uid, and newpassword is replaced with your new password. Keep the quotes in the command.

Do not use special characters in your password, such as: ` !#'"`&;$\\ ` or spaces.

### Test a simple query

First, you must choose which database you want to work in. You can see which databases are available to you by running the command:

`show databases;`

You should see one named with your uID, Chess, and Library, in addition to some standard databases MySQL always creates.

Select which one you want to use by typing (for example)

`use Library;`

Now you should be able to see the Library tables:

`show tables;`

And you can run simple select queries, such as:

`select * from Titles;`

**WARNING**

In general, avoid commands that may select large amounts of data (such as select * without a filter). It's fine on the Library since it is a small database, but do not do this regularly on the Chess database. 

## Part 2 - Creating the Dealership

In this part, you will create the car dealership database from [Lab 1](lab1.md). Put all the necessary tables into your private database (the one named with your uID). Switch to your uID database now by running:

```
use uYOURUID;
```

When creating your tables, the string datatypes should not be larger than 255 characters. You should also add "unsigned" where appropriate on the integer types.

Note that the tables shown in Lab 1 do not specify foreign keys, but you must add foreign keys as appropriate to your real tables.

Think about the foreign keys and other constraints you might need to add to your tables in the dealership database. For example, for the table that represents who is selling which car(s), can a VIN exist in a that table if it doesn't exist in your cars table?

Once you have created your tables, populate them with all the data specified in Part 3 of Lab 1.

Do not be afraid to drop your tables and start again if you mess up. It's probably easier than trying to fix them with alter commands. This is not true in general, but is true for tiny databases like this.

## Part 3 - Simple Retrieval Queries

Switch to the `Library` database, and create queries to find the specified information below. Some of these are quite simple, and we have already seen them. Note that the Library has some additional information in it to make the queries more interesting. The slides shown in class do not contain the full instances.  These questions contain "variables" in angle brackets which are described below.

When testing out your queries, you can replace the variables such as `<Author>` with an author that you know is in the database, such as "Herbert". However, when you hand in your solution, put the placeholder back into the query.


* Get the Titles of all books by `<Author>`
```
select Title from Titles where Author='<Author>'
```
* Get Serial numbers of all books by `<Author>`
```
select Serial from Titles natural join Inventory where Author='<Author>'
```
* Get the Titles of all books checked out by `<Patron’s name>`
```
select Title from CheckedOut natural join Patrons natural join Inventory natural join Titles where Patrons.Name='<Patron's name>'
```
* Get phone number(s) of anyone with `<Title>` checked out
```
select Phone from CheckedOut natural join Phones natural join Inventory natural join Titles where Title='<Title>'
```


## Part 4 - Intermediate Retrieval Queries

* Find the Titles of the library's oldest `<N>` books. Assume the lowest serial number is the oldest book.
```
select Title from (select * from Titles natural join Inventory order by Serial asc limit <N>) as T
```
* Find the name of the person who has checked out the most recent book. Assume the highest serial number is the newest book. Hint: the highest serial number book may not be checked out by anyone.
```
select Name from (Patrons natural join CheckedOut natural join (select * from (select * from Titles natural join Inventory order by Serial desc limit 1) as T) as T2 )
```
* Find the phone number(s) of anyone who has not checked out any books.
```
select Phone from Phones where CardNum not in (select CheckedOut.CardNum from CheckedOut)
```
* The library wants to expand the number of unique selections in its inventory, thus, it must know the ISBN and Title of all books that it owns at least one copy of. Create a query that will return the ISBN and Title of every book in the library, but will not return the same book twice.
```
select distinct ISBN, Title from Inventory natural join Titles
```

## Part 5 - Chess Queries
For this part, switch to the Chess database.

*Be careful with your queries in this database* This one has a lot of data, and a poorly formed query could easily overwhelm the server. If you repeatedly run very expensive queries, your account will be locked.

Note that the schemas in this database have some additional columns that were not shown in Lab 3, and the Result column in the Games table is encoded as 'W', 'B', or 'D', for white winning, black winning, or draw. Also note that names are given as "last, first", so Magnus Carlsen is listed as "Carlsen, Magnus". Feel free to run "describe" commands on the tables in the Chess database.

Provide SQL queries for the six relational queries in Lab 3, Part 2.

```
select distinct Name from Players where Elo>=2850
```
```
select distinct Name from Players join Games G on Players.pID = G.WhitePlayer
```
```
select distinct Name from Players join Games G on Players.pID = G.WhitePlayer and G.Result = 'W'
```
```
select distinct Name from Players join (select whitePlayer, blackPlayer from (Events join Games G on Events.eID = G.eID and year(Date) = 2018)) as T where pID = T.BlackPlayer or pID = T.WhitePlayer
```
```
select distinct Name, Date from Events join (select eID from (Players join Games G on (pID = G.WhitePlayer and Result = 'B') or (pID = G.BlackPlayer and Result = 'W')) where Name = 'Carlsen, Magnus') as T where T.eID = Events.eID
```
```
select distinct Name from Players
    join (
    select BlackPlayer, WhitePlayer from (
        Players join Games G on pID = G.WhitePlayer or pID = G.BlackPlayer
        ) where Name = 'Carlsen, Magnus') as T
where Name != 'Carlsen, Magnus' and (WhitePlayer=Players.pID or BlackPlayer=Players.pID)
```


## Part 6 - Adv. Retrieval Queries (Not graded yet)

These queries will be difficult without the material from Lecture 9, which we've only partiall covered, but feel free to attempt them.

* Find the name of the patron who has checked out the most books.
```
select Name from Patrons natural join (
    select CardNum from CheckedOut group by CardNum order by count(*) desc limit 2
) as T
```
* Find the Authors who have written more than one book. Assume that two Authors with the same name are the same Author for this query.
```
select Author from Titles group by Author having count(*) > 1
```
* Find the Authors for which the library has more than one book in inventory (this includes multiple copies of the same book). Assume that two Authors with the same name are the same Author for this query.
```
select Author from Titles natural join Inventory group by Author having count(*) > 1
```


### Killing Queries

If properly formed, these queries should all run in a few seconds, including the network transfer time. The computational parts should all run in a fraction of a second, assuming nobody else is overwhelming the server. To kill a query that is taking too long, the simplest approach is to press ctrl-c, which will disconnect you. A better approach is to open another mysql client in another terminal and run "show processlist;". Find the ID of your process, and run "kill query <id>;"

### Hints

Be careful with natural join - both Players and Events have a column called "Name", which have different meanings (but SQL doesn't know this). Trying to natural join any temporary relation with those two columns will not have the desired result, even if the relations do both have "eID". To be safe, don't use natural join.
Be careful when mixing "and" and "or" in boolean conditions. It's always safest to be explicit with parenthesis. For example, (false and false or true) is not the same as (false and (false or true)). Getting this wrong can result in very expensive queries.


## What to submit
For Part 2, we will simply look at the structure and contents of your database, and make sure it contains the right tables with the right data.

For Parts 3 - 6, commit a markdown file containing your SQL queries to your git repo.