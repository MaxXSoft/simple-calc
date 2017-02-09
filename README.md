# simple-calc
A simple calculator based on a recursive descent parser.

### Usage
Build and then run in terminal. You will see this information: 
```

a simple expression calculator by MaxXing
based on a recursive descent parser

 input > _
```
Enter the mathematical expression ending with a question mark after the **input >** cursor. Like: 
```
 input > 1 + 1 ?
```
All of the spaces in your input will be ignored.

Then press enter: 
```
 input > 1 + 1 ?
result > 2.000000
 input > _
```
The result is 2.

### Supported Operators
This calculator supports only the following operators：
* **Brackets:** (, )
* **Mathematical operation:** **, *, /, %, +, -
* **Bit operation:** <<, >>, &, ^, |
* **Logical operation:** <=, <, >=, >, ==, !=

### Reference
* LLVM Tutorial: [Kaleidoscope: Implementing a Parser and AST](http://llvm.org/docs/tutorial/LangImpl02.html)
