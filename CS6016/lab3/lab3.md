# Lab 3: Relational Algebra

For this assignment you will hand in a pdf or a Markdown file **that renders properly on Github** that containing relations (tables) and relational algebra queries.  Github recently added support for Latex-based "math mode" formatting so you can embed Latex directly in a MD file.  (Mactex's preview mostly matches what I see on Github, but it's not exactly the same.  Make sure you check what's visible on Github after you commit your work!).  Take a look at the source for this document to see examples of doing Latex style formatting.

If you want to make a PDF, we recommend using Microsoft Word or Latex to generate your pdf. Feel free to copy characters from [this word document](https://www.cs.dartmouth.edu/~cs61/Resources/Examples/RAsymbols/rasymbols.doc) containing relational algebra symbols. Make sure to use proper subscript where appropriate. If you want to use Latex, [this template](latexTemplate.tex) should be a good starting point.  You can install 2 casks from homebrew to get you all the Latex stuff you need and a nice editor by running `brew install --cask mactex texshop`.  TexShop is the editor application.  Feel free to reach out with questions about Latex.

For all relational algebra queries, use the compound operators such as divide and natural join where appropriate. Points may be deducted if your query is needlessly complex.

## Part 1 - Joins
Consider the following relations:

### T1

|A|Q|R|
|---|---|---|
|20|a|5|
|25|b|8|
|35|a|6|


### T2

|A|B|C|
|---|---|---|
|20|b|6|
|45|c|3|
|20|b|5|

Provide the relations that result from the following queries. Your relations should be in the form of a table, and should include the schema.

1. $ T1 \bowtie_{T1.A = T2.A} T2 $

|T1.A|Q|R|T2.A|B|C
|---|---|---|---|---|---|
|20|a|5|20|b|6|
|20|a|5|20|b|5|


2. $ T1 \bowtie_{T1.Q = T2.B} T2 $

|T1.A|Q|R|T2.A|B|C
|---|---|---|---|---|---|
|25|b|8|20|b|6|
|25|b|8|20|b|5|

3. $ T1 \bowtie T2 $

|T1.A|Q|R|B|C
|---|---|---|---|---|
|20|a|5|b|6|
|20|a|5|b|5|

4. $ T1 \bowtie_{T1.A = T2.A \wedge T1.R = T2.C} T2 $

|T1.A|Q|R|T2.A|B|C
|---|---|---|---|---|---|
|20|a|5|20|b|5|

## Part 2 - Chess Queries

Consider the schemas below for a Chess database, similar to the one you designed in Homework 2, except some columns are left out for simplicity. Note that the instance data given is just to show an example, and it may change (you can't hard-code your queries based on these instances).

### Events

|Name|Year|eID|
|---|---|---|
|World Championship|1987|1|
|Moscow Open|2018|2|
|World Championship|2018|3|

### Players

|Name|Elo|pID|
|---|---|---|
|Magnus Carlsen|2882|1|
|Judit Polgar|2735|2|
|Fabiano Caruana|2844|3|
|Gary Kasparov|2851|4|
|Anatoly Karpov|2780|5|

### Games: wpID (white) and bpID (black) reference pID from Players

|gID|eID|Result|wpID|bpID|
|---|---|---|---|---|
|1|3|1/2-1/2|1|3|
|2|3|1/2-1/2|3|1|
|3|2|1-0|2|1|
|4|1|1/2-1/2|4|5|
|5|3|0-1|3|1|

Recall that in this database, a result of "1-0" means white won, "0-1" means black won, and "1/2-1/2" means it was a draw. 

Hint: you can't natural join Games with Players because they have no columns with the same name.

Write relational algebra queries for the following. You can (and should) write your query on multiple lines if you use the renaming operator.

1. Find the names of any player with an Elo rating of 2850 or higher. $ \Pi_{Name}(\sigma_{Elo \geq 2850}(Players)) $
1. Find the names of any player who has ever played a game as white. $ \Pi_{Name}(Players \bowtie_ {Players.pID = Games.wpID}Games)$
1. Find the names of any player who has ever won a game as white. $ \Pi_{Name}(Players \bowtie_ {Players.pID = Games.wpID \wedge Games.Result = 1-0}Games)$
1. Find the names of any player who played any games in 2018. $ \Pi_{Players.Name}(Players\bowtie_{Players.pID = Games.wpID \vee Players.pID = Games.bpID}(Events\bowtie_{Events.eID = Games.eID \wedge Events.Year = 2018}Games))$
1. Find the names and dates of any event in which Magnus Carlsen lost a game.
$ \Pi_{Events.Name, Year}(Events \bowtie_{Events.eID = Games.eID}(\sigma_{Name=Magnus \ Carlson}(Players \bowtie_{(pID = wpID\ \wedge \ Result=0-1)\ \vee \ (pID=bpID \ \wedge \ Result = 1-0)}Games)))$
1. Find the names of all opponents of Magnus Carlsen. An opponent is someone who he has played a game against. Hint: Both Magnus and his opponents could play as white or black.
$ \Pi_{Name}(\sigma_{Name\neq Magnus \ Carlson}(Players \bowtie_ {Players.pID = Games.wpID \vee Players.pID=Games.bpID}(\Pi_{wpID, bpID}(\sigma_{Name=Magnus \ Carlson}(Players \bowtie_ {pID=wpID \vee pID=bpID}Games))))$


## Part 3 - LMS Queries
Consider [this basic database for a learning management system](students.pdf).

### Part 3.1:

a) Provide the relation that is the result of the following query. Your relation should be in the form of a table, and should include the schema.

$ \rho(C, \pi_{sid}(\sigma_{Grd=C}(Enrolled)))$

|C.sID|
|---|
|3|
|4|

$\pi_{Name}((\pi_{sid}(Enrolled) - C)\bowtie Students)$

|Students.Name|
|---|
|Hermione|
|Harry|

b) Provide a simple English description of what the query is searching for. Your description should be in general terms (remember that the original LMS instance data may change).

Answer:
First, the query is selecting students who got a C grade from the Enrolled schema, then projecting sID column, and then renaming that relation to C.
Second, the query is removing sID 3 and 4 from the enrolled schema and then isolating the sID 1 and 2 using natural join and then projecting the Name attribute.
 

### Part 3.2:

a) Provide the relation that is the result of the following query. Your relation should be in the form of a table, and should include the schema.

$ \rho(S1, Students) $
|S1.sID|S1.Name|S1.DOB|
|---|---|---|
|1|Hermione|1980|
|2|Harry|1979|
|3|Ron|1980|
|4|Malfoy|1982|

$ \rho(S2, Students) $

|S2.sID|S2.Name|S2.DOB|
|---|---|---|
|1|Hermione|1980|
|2|Harry|1979|
|3|Ron|1980|
|4|Malfoy|1982|

$ \pi_{S2.Name}(\sigma_{S1.Name == Ron \wedge S1.DOB == S2.DOB \wedge S2.name != Ron}(S1 \times S2))$

|S2.Name|
|---|
|Hermione|



b) Provide a simple English description of what the query is searching for. Your description should be in general terms (remember that the original LMS instance data may change).

Answer: This query is searching for students who have the same DOB as Ron, excluding him.
 

### Part 3.3:

a) Provide the relation that is the result of the following query. Your relation should be in the form of a table, and should include the schema.

$\pi_{Name}((\pi_{cid, sid}(Enrolled)/\pi_{sid}(Students))\bowtie Courses)$

|Courses.Name|
|---|


b) Provide a simple English description of what the query is searching for. Your description should be in general terms (remember that the original LMS instance data may change).

Answer: This query is asking for the name of courses that every student has taken. With the current dataset though, there are no courses that every student has taken.
 

## Part 4

Provide a relational algebra query that uses the divide operator to find the names of all students who are taking all of the 3xxx-level classes.

$ \Pi_{Name}((\Pi_{sID, cID}(Enrolled) / \Pi_{cID}(\sigma_{cID \geq 3000 \wedge cID \geq 4000}(Enrolled))) \bowtie Students) $

Commit your .md or .pdf file to your git repo (It's probably a good idea to include your .tex or .docx file as well, but we'll only look at the PDF).