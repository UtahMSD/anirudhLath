# Lab 5: Finish the bonus queries from lab 4

## Due Tuesday, June 22

This lab will be worth less than the previous ones because it's a lot shorter.

Submit a MD file that contains your queries to answer the following questions on the Library database.

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

* The library wants to implement a customer loyalty program based on how many books each patron has checked out. Provide an SQL query that returns the names, number of books they have checked out, and loyalty level of each Patron. The loyalty level should be the string "Platinum" if they have checked out > 2 books, "Gold" if they have 2 books, "Silver" if they have 1 book, and "Bronze" if they have no books. Hint: remember that NULL represents an unknown in SQL (it does not represent 0).

```
select Name, count(Serial) as NoOfBooksCheckedOut,
CASE
    WHEN count(Serial) > 2 THEN 'Platinum'
    WHEN count(Serial) = 2 THEN 'Gold'
    WHEN count(Serial) = 1 THEN 'Silver'
    WHEN count(Serial) = 0 THEN 'Bronze'
END as LoyaltyLevel
from Patrons left join CheckedOut CO on Patrons.CardNum = CO.CardNum group by Name
```
