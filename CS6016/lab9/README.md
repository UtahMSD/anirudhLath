# Lab 9: Indices: Due Tuesday, 7/26

In this lab, we will practice reasoning about indexes in a DBMS. Write your answers in Markdown or some other format that's easy to read on Github and commit them to your repo.

## Part 1 - Selecting Indexes

For each situation described, specify the minimal set of additional secondary indexes you should add to the table(s) to efficiently support all the queries, and briefly explain your reasoning. If no additional indexes are needed, write "None" for your answer. Assume all databases are very large.

Do not add any unnecessary indexes. Do not use indexes that are more complex than needed.

Recall that the primary key already has a primary index, but assume that we have NOT specified any foreign key constraints, so there won't be any indices automatically provided for them.

### A database contains the following table for former-employee records:

|eID (int) (primary key)| Start Date (Date)|End Date (Date)|
|---|---|---|

There are two common queries performed on this table:

* Find all employees that started after a certain date
* Find all employees that started on a certain date, and worked until at least another certain date

**Based on the queries, I think we need 2 indexes, one for start date and one for end date since we are querying by start date and end date.**


### A database contains the following table for tracking student grades in classes

| studentID (int) (primary key)| className (varchar(10)) (primary key)| Grade (char(1))|
|---|---|---|

This table only tracks whole letter grades, no '-' or '+' modifiers. Assume many students can take a class, and a student can take many classes. The primary key is created in the order (studentID, className).

The common queries performed on this table are:

* Get all grades for a particular student
* Get all classes for a particular student
* Get all students with a grade better than 'B'
* Get all classes where any student earned a grade worse than 'D'

**Based on the queries, I think we need an index for grades as we will be looking up by grades.**

### Using the same grade database, but now the common queries are:

* Get all classes ordered by class name
* Get all students who earned an 'A' in a certain class

**Again, we will need an index for grades because we are querying by grades.**

### Queries on the chess database

Assume the only existing indexes are the primary index on each table (despite whatever indexes are on the actual tables.  Remember, we're assuming there are NOT indexes created for foreign key constraints). Also assume the actual table sizes in the Chess database (ie big).

Common queries are:

* `select Name from Players where Elo >=2050;`
* `select Name, gID from Players join Games where pID=WhitePlayer;`

**Based on these queries, there should be an index for Elo and WhitePlayer each since we are querying by Elo and joining by WhitePlayer.**

### Queries on the public Library database

 Assume the only existing indexes are the primary index on each table (despite whatever indexes are on the actual tables).

Common queries are:

* `select * from Inventory natural join CheckedOut;`

**No indexes needed here, both tables already have indexes on Serial since it's the primary key.**

### More library queries:

Assume the only existing indexes are the primary index on each table (despite whatever indexes are on the actual tables).

Common queries are:

* `select * from Inventory natural join CheckedOut where CardNum=2;`
* `select * from Patrons natural join CheckedOut;`

**Index needed on CheckedOut.CardNum since we are querying and joining based on it.**

### Still more library queries

Assume the only existing indexes are the primary index on each table (despite whatever indexes are on the actual tables). Also assume that the Library has been auto-scaffolded as discussed in class.

```
var query =
  from t in db.Titles
  select new
  {
    Title = t.Title,
    Serials = from i in t.Inventory select i.Serial
  };
```
**We can add an index on Inventory.ISBN since we are joining Titles and Inventory based on ISBN to extract the serials.**
## Part 2 - B+ Tree Index Structures

Answer the following questions about index structures and record storage. Assume the DBMS uses 4096-byte pages.

For simplicity, assume that B+Tree child pointers do not occupy any disk space (all internal node storage is devoted to storing keys). Ignore any other potential overhead data such as next page pointers, counts, etc. 

### Students table:

Consider the students table from #2 in Part 1 above. Assume that an int occupies 4 bytes, and a varchar(10) occupies 10 bytes.


* How many rows of the table can be placed into the first leaf node of the primary index before it will split?

**4096 / (4 + 10 + 1) ~ 273 rows since leaf nodes contain the whole rows.**

* What is the maximum number of keys stored in an internal node of the primary index? (Remember to ignore pointer space. Remember that internal nodes have a different structure than leaf nodes.)

**4096 / (4 + 10) ~ 292 keys since internal nodes only contains the key.**

* What is the maximum number of rows in the table if the primary index has a height of 1? (A tree of height 1 has 2 levels)

**A tree of height 1 will have 292 + 1 child nodes and each leaf node will have 273 rows in it. Therefore the maximum number of rows is 293 * 273 = 79,989 rows.**

* What is the minimum number of rows in the table if the primary index has a height of 1? (A tree of height 1 has 2 levels)

**The root node will split only when the rows have exceeded the maximum value of 273 rows and the minimum value for a split will be 273 + 1 rows. Therefore, 274 is the minimum number of rows in a height of 1.**

* If there is a secondary index on Grade, what is the maximum number of entries a leaf node can hold in the secondary index?

**It should be 4096 / (14 bytes from primary key + 1 byte from index) = 273 entries.**

### Another table

Assume that for some table, rows occupy 128 bytes.

* What is the maximum number of leaf nodes in the primary index if the table contains 48 rows? 

**4096 / 128 = 32 rows maximum on each leaf node. Therefore, maximum number of leaf nodes will be 2 since 2 nodes * 32 rows = 64 rows which is enough to hold 48 rows.**
* What is the minimum number of leaf nodes in the primary index if the table contains 48 rows?

**Same, the minimum leaf nodes will be 2 as well because one leaf node can only hold 32 rows which is not enough to hold 48 rows therefore 2 leaf nodes, which can store 64 rows is enough and is the minimum required number of nodes for storing 48 rows.**

