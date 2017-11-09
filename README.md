# sunset

Add support for pictures

A ultility that transforms markdown files to json


## Paragraph types

Paragraphs is sort of a misnomer in this case consindering the fact that other data types are stored in this array.

| Type    | Type ID  | 
| -------------- |:-:|
| Heading 1      | 1 |
| Heading 2      | 2 |
| Heading 3      | 3 |
| Heading 4      | 4 |
| Heading 5      | 5 |
| Paragraph      | 6 |
| Heading 6      | 7 |
| Code Block     | 8 |
| Unordered List | 9 |
| Ordered List   | 10 |
| Image          | 11 |


## Markup Types

List of currently supported markups. These are usually included in a paragraph object. It contains information about the type of markup, start, end, and other metadata.

| Type     | Type ID | 
| -------------- |:-:|
| Italic         | 1 |
| Bold           | 2 |
| Link           | 3 |
| Code           | 4 |
| Underline      | 5 |
| Strike Through | 6 |


