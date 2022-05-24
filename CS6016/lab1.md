# Part 1

Answer 1:
SKU is always unique from product to product, therefore, that is used as the key in this case.

`
Inventory [__SKU__ (integer), name (string), quanity (integer), price (real)]
`

Answer 2:
SKU and Aisle are used as the key since it will not allow a product of the same SKU to be displayed twice in the same aisle.

`
Location [__SKU__ (integer), __aisle__ (integer), name (string)]
`

Answer 3:
VIN is unique to every vehicle and SSN is unique to every US citizen, therefore they should be enough to be used as the key and will allow the dealership to assign multiple salesperson to each car.

`
SalesList [__VIN__ (string), __SSN__ (string), make (string), model (string), year (integer), color (string), salesperson (string)]
`

# Part 2

```
CREATE TABLE Inventory (
    Serial int,
    ISBN char(14),
    PRIMARY KEY (Serial),
    FOREIGN KEY (ISBN) REFERENCES Titles(ISBN)
)

CREATE TABLE Patrons (
    Name string,
    CardNum int,
    PRIMARY KEY (CardNum)
)

CREATE TABLE CheckedOut (
    CardNum int,
    Serial int,
    PRIMARY KEY (Serial),
    FOREIGN KEY (Serial) REFERENCES Inventory(Serial),
    FOREIGN KEY (CardNum) REFERENCES Patrons(CardNum)
)

CREATE TABLE Phones (
    CardNum string,
    Phone char(8),
    PRIMARY KEY (CardNum, Phone),
    FOREIGN KEY (CardNum) REFERENCES Patrons(CardNum)
)

CREATE TABLE Titles (
    ISBN char(14),
    Title string,
    Author string,
    PRIMARY KEY (ISBN)
)
```

# Part 3
| VIN | Salesperson | Make | Model | Year | Color | SSN |
| --- | --- | --- | --- | --- | --- | --- |
| 1GKDT13W6P2533357 | Hannah | Toyota | Tacoma | 2008 | Red | 123-456-7890 |
| 4T1SK12E7PU300490 | Arnold | Toyota | Tacoma | 2008 | Red | 234-567-8901 |
| JNKCV61E49M014581 | Arnold | Toyota | Tacoma | 1999 | Green | 234-567-8901 |
| 3C3CFFER6CT225038 | Steve | Tesla | Model 3 | 2018 | White | 345-678-9012 |
| JH4KA8170MC002642 | N/A | Subaru | WRX | 2016 | Blue | N/A |
| JM3TB2MA5A0235007 | Hannah | Ford | F150 | 2004 | Red | 123-456-7890 |

# Part 4
|Attribute Sets|Superkey?|Proper Subsets|Key?|
|---|---|---|---|
|{A1}|No|{}|No|
|{A2}|No|{}|No|
|{A3}|No|{}|No|		
|{A1, A2}|Yes|{A1}, {A2}|Yes|
|{A1, A3}|No|{A1}, {A3}|No
|{A2, A3}|No|{A2}, {A3}|No|
|{A1, A2, A3}|Yes|{A1}, {A2}, {A3}|No|

# Part 5
* If {x} is a superkey, then any set containing x is also a superkey. - False, the other set may have duplicate values of {x}.
* If {x} is a key, then any set containing x is also a key. - False, the other set may have duplicate values of {x}.
* If {x} is a key, then {x} is also a superkey. - True, all keys can be classified as superkeys.
* If {x, y, z} is a superkey, then one of {x}, {y}, or {z} must also be a superkey. - False, only the combination of each attribute value has to be unique.
* If an entire schema consists of the set {x, y, z}, and if none of the proper subsets of {x, y, z} are keys, then {x, y, z} must be a key. - True, if an entire schema is made up of {x, y, z} and none of the proper subsets are key, that makes {x, y, z} the minimal subsets of unique values hence making it a key.