# POWER-KI (PWK) - Programming Language
**© XPLAB - Research in Automation - Brescia - Italy - Europe**

## Table of Contents
1. [Application Structure](#application-structure)
2. [Execution and Parameters](#execution-and-parameters)
3. [ASSEMBLY](#assembly)
4. [Items and Primary Elements](#items-and-primary-elements)
5. [Control Components](#control-components)
6. [CODE - Programming](#code---programming)
7. [Operators](#operators)
8. [System Functions](#system-functions)
9. [Flow Instructions in CODE](#flow-instructions-in-code)
10. [Coding Examples](#coding-examples)
11. [BASKET](#basket)
12. [Multi Threading](#multi-threading)
13. [GUI and Native Cloud](#gui-and-native-cloud)

---

## Application Structure

The executable code part in PWK is enclosed in units called **ASSEMBLY**. There are two types of applications:

### Single ASSEMBLY (.pka)
Independent files that can be executed as console commands.

### Package (.pwk)
Container that includes:
- One or more ASSEMBLY
- Interface elements (GUI - GraphicUserInterface, WUI - WebUserInterface)
- Resources (graphic elements)
- Possible WRAP DLLs
- Other necessary elements defined by the programmer

In Packages, the **Main** ASSEMBLY is declared, which is executed when the application starts. The Package is described by a **Manifest** managed by specific functions.

---

## Execution and Parameters

### Automatic Configuration
At creation time, a VAR is automatically inserted into the ASSEMBLY containing:
- **VAR Editor**: configuration parameters for editing
- **VAR Executor**: configuration parameters for execution

### Executor Parameters
If the ASSEMBLY is single or defined as MAIN in the package:
- **EXO attribute**: contains the name of the EXO to execute at startup (default: Main)
- **LIMIT_ONCE=YES** + **LIMIT_KEY**: limit execution to one copy per PC

### Command Line Parameters
At startup, parameters can be passed that will be available:
- In the LIS whose PTR is contained in `parlis@\pwk\Executor`
- In attributes P1, P2, etc. (if defined)
- Directly in the entry point EXO attributes:
  ```
  MyProgr.pwk mypar1=one mypar2=two
  ```

---

## ASSEMBLY

### Items, Attributes and References
ASSEMBLYs are a "forest" of **ITEMS**, each of which can contain other ITEMs. Each ITEM (except CODEs) can have **ATTRIBUTES** with numeric (NV) or non-numeric (NNV) values.

Attributes that start and end with "_" are reserved for PWK (e.g. `_OS_`).

### Paths (PATH)
ITEMs are identified through **ABSOLUTE** or **RELATIVE** paths:
- **Absolute**: `\item\item\item`
- **Relative**: `item\item\item`
- **In LIBs**: `\\item\item\item` (reference to parent ASSEMBLY)

### Attribute References
- **Implicit**: `att`
- **Relative**: `att@itm`
- **Absolute**: `att@\itm`
- **Indirect**: `{X}` or `REF` function

References are resolved relative to the executive item. If the element is a MTHD, resolution extends to the parent element (EXO, VAR, GUI).

---

## Items and Primary Elements

### EXO (EXcutable Object)
```
>> (EXO) MyExo
```
Executable element similar to functions. Can be defined as **EXOsync** to serialize calls from different threads.

**Invocation**:
- Flow commands: `EXEC`, `EXECsync`, `THREAD`
- Within CODE: `EXC`, `EXCTHR` functions

**Characteristics**:
- Attributes with SET, GET, SET+GET types automatically proposed in workbench
- If not SYNC, attributes are not persistent

### MTHD (Method)
```
>> (MTHD) MyMethod
```
Equivalent to EXOs but can only be defined within VAR or EXO.

### VAR
```
>> (VAR) Myvar
```
Container items that can contain other VARs and MTHDs. VAR attributes are **persistent** and **visible** to all ITEMs.

### GUI - Graphic User Interface
```
>> (GUI) MyGui
```
Element for connection between ASSEMBLY and GUIs defined by .pki files. Equivalent to VARs but with predefined attributes and elements.

**Operation**:
- GUIs with `_AUTOLOAD_=ON` are automatically sent to PWK-GUI-X01.exe
- Use of `_ADDR_` and `_PORT_` attributes for configuration
- Automatic **trig** method to receive user interactions

---

## Control Components

### WHILE
```
>> (WHILE) while
--> (PRE) pre
--> (DO) do
--> (DONXT) donxt
```
- **PRE**: executed once unconditionally
- **DO**: executed while `_COND_` is true
- **DONXT**: executed at the end of DO if it was executed at least once

**Controls**:
- **CONT**: goes to next iteration
- **BREAK**: terminates the WHILE

### IF
```
>> (IF) if
--> (THEN) then
--> (ELSE) else
```
Executes THEN if `_COND_` is true, otherwise ELSE.

### SWITCH
```
>> (SWITCH) SelectCase : Mycase1;...;MycaseX
-->(CASE) MyCase1
-->(CASE) ...
-->(CASE) MycaseX
```
Searches for an attribute value among CASE values. Supports state logic through dynamic re-evaluation.

### Evaluation Components
```
>> (TRUE) MyValue    # Activated if attribute is true
>> (FALSE) MyValue   # Activated if attribute is false
>> (ONERR) MyValue   # Activated for errors (NULL or <0)
```

### Containers
```
>> (LBL) MyLabel     # Label - executed in normal flow
>> (BLK) MyBlk       # Block - only reachable via CALL/GOTO
```

### Control Directives
```
>> (CALL) MyBlk      # Call with return
>> (GOTO) MyLbl      # Definitive transfer
```

### EXO/MTHD Execution
```
>> (EXEC) \MyExo     # Synchronous execution
--> (SET) set        # Call parameters
--> (GET) get        # Return values

>> (EXECsync) \MyExo # Serialized execution
>> (THREAD) MyExo    # Execution in separate thread
```

**THREAD Parameters**:
- `_PAR_`:
  - **ONCE**: execute only if not already running
  - **ONCE_FOR_CALLER**: for same calling thread
  - **SYNC**: synchronous execution
- `_RSLT_`: result (-10=error, -1=failed, 0=starting, 1=started)

### Other Components
```
>> (CALC) MyFormula  # Code execution from symbol (deprecated)
>> (BREAK) break     # Interrupt loops/switch
>> (END) end         # ASSEMBLY termination
```

---

## CODE - Programming

### General Characteristics
- C-like syntax
- Content encodable in RTF or plain Unicode
- Only ATTRIBUTES, operators, library functions, temporary variables
- Instructions end with semicolon
- PWK is case insensitive
- Index base: 1 (1bsd)
- PTRs must be TRASHed after use

### Temporary Variables
- **Local (LTV)**: `°a=10;` - visible at EXO/MTHD level
- **Global (GTV)**: `°b°=20;` - persistent and visible to Thread

---

## Operators

### Basic Operators
- **Arithmetic**: `+`, `-`, `*`, `/`, `//` (integer division), `^` (power), `%` (modulo)
- **Comparison**: `==`, `<>`, `!=`, `<`, `>`, `<=`, `>=`
- **Logical**: `AND`, `OR`, `XOR`, `NOT`
- **Binary**: `&`, `|`, `%`, `!`
- **Shift**: `<<`, `>>`, `<<=`
- **Assignment**: `=`, `+=`, `-=`

### Special Operators

#### $ (address)
```c
WAITCND($V1, £NOTNULL);
```

#### £ (literal)
```c
£test;  // equivalent to "test"
```

#### :: ? -> (SET/GET Parameters)
```c
r1=EXO("\TEST", a::p1, b::p2, ?r1, ?r2, ?r3)->r3->r2;
```

#### {} (indirect addressing)
```c
a="p1@\main"; 
{a}=10;  // assigns 10 to p1@\main
```

#### ~ (tilde)
```c
IF(~v1, £full, £empty);  // true if v1 is not null/empty
```

#### += -= (atomic operators)
Guarantee thread-safe operations:
```c
A+=1;  // atomic increment
```

#### / (special division)
Division by ZERO returns ZERO.

#### == vs CMP
```c
s1="first"; s2=" first "; s3=" First";
c1=if(s1==s2, £YES, £NO);     // YES (ignores spaces/case)
c2=if(s1 cmp s2 == 0, £YES, £NO);  // NO (precise comparison)
```

#### << >> (Context-aware shift)
```c
a=0b1101; b=a>>2;        // b=0b11 (numeric)
A="Tested"; B=A>>2;      // B="Test" (string)
```

#### ++ <<= (concatenation)
```c
C = A ++ B;    // concatenation without space
C = A <<= B;   // equivalent
```

#### .. (concatenation with space)
```c
C = A .. B;    // concatenation with space
```

### Fuzzy and Probabilistic Operators
- **Fuzzy**: `ZNOT`, `ZAND`, `ZOR`, `ZXOR`, `ZSUM`, `ZFSUM`
- **Probabilistic**: `PAND`, `POR`, `PXOR`

---

## System Functions

### References
- **REF**: indirect reference
- **EXIST**: verify ITEM/attribute existence
- **TYPOF**: return ITEM/attribute type

### Conversions
- **HEX**, **BIN**: base conversion
- **FLT**: float with specified decimals
- **INT**, **UNS**: numeric conversions
- **CHAR**: encode NV to symbol
- **CHARCOD**: character numeric code

### Value Control
- **MIN**, **MAX**: minimum/maximum of value list
- **LIM(v, mn, mx)**: value limited between extremes

### Conditional Functions
- **IF(c, a, b)**: ternary - all parameters are evaluated

### Test and Validation
- **ISNULL(x)**: true if x is NULL
- **ISEMPTY(x)**: true if x is empty (not NULL)
- **ISTRUE(x)**: true if x>0 (NV) or not empty (NNV)
- **ISERR(x)**: true if NULL or <0
- **TSTX(x, "One,Two")**: returns £One if x true, £Two otherwise
- **ISNUM(x)**: true if x is NV
- **ISFLT(x)**: true if x is NV of type FLT

### Symbol Manipulation
- **BITF**: bit field extraction/modification (NV)
- **MID**: character field extraction/modification (NNV)
- **LEN(s)**: symbol length
- **NSP(s)**: remove leading/trailing spaces
- **FST(s)**, **LST(s)**: first/last character
- **CAT**: concatenation
- **LWR(s)**, **UPR(s)**: lowercase/uppercase
- **RTF2TXT(x)**: RTF to Unicode conversion
- **NNL(x)**: empty string if NULL
- **NNLv(x,v)**: value v if x is NULL

### Formatting
- **FRMT**: C printf-style formatting

### Symbol Division
- **SPLT**: Left/Right side extraction with separator
- **TKNZ/TKNZOP**: LIS from symbol with separator list
- **CSV**: LIS with comma separator
- **CSVTBL**: TBL with element/row separators

### Symbol Search
- **SRCH**: search symbol within another symbol
- **MTCH**: symbol similarity comparison

### Quote Management
- **QUOS**: surround with single quotes
- **QUOD**: surround with double quotes
- **QUOSE**, **QUODE**: preserve internal quotes by doubling
- **ESCP**: escape characters

### Time
- **TMR**: system time in ms (high resolution)
- **CLOCK**: seconds since January 1, 1970

### Execution
- **EXC**: EXO call from CODE
- **EXCTHR**: EXO launch in new THREAD
- **EXCFLUSH**: EXO cache cleanup
- **CALC**: code execution from symbol

### Wait and Synchronization
- **YIELD**: time slice release
- **SLEEP(x)**: suspend x milliseconds
- **WAITCND**: wait for condition on symbol

### Output
- **CNS**: show/hide console
- **CNSOUT**: console output
- **ERROUT**: std error output
- **ERRSHW**: system error output
- **STDINP**: stdin input
- **STDOUT**: stdout output

### Chat
- **CHATMSG**: number of queued messages
- **CHATPUT**: send message
- **CHATGET**: first queued message
- **CHATCLR**: delete messages
- **CHATSHW**: all messages separated by CRLF

### Triggers
- **TRIG**: service function activators
- **TRIGSET**, **TRIGPAR**: (deprecated)

### Operating System
- **OSEXEC**: synchronous OS command
- **OSSHELL**: OS command
- **OSSTART**: start new process
- **PWKTASK**: start PWK program as process

### Thread Management
- **THRINF**: running thread information
- **THRSYM**: Auto attribute management
- **THRPRI**: thread priority change

### Pointer Management
- **PTRTYP**: PTR information
- **PTRLIS**: allocated pointer list
- **PTRDUP**: pointer duplication
- **TRASH**: PTR elimination

### Reflective Functions
- **THIS**: current CODE address
- **DBGLINE**: current line number
- **DBGINFO**: debug information
- **LIBINFO**: system library information

### Synchronization
- **SMF**: semaphore management
- **DOOR**: door management

### Paths
- **ALIASPTH**: alias for root element path
- **PKGPTH**: Package path
- **PWKPTH**: PWK installation directory path
- **PRGPTH**: running program path

### Constants
- **CRLF**: end of line (0x0d0A)
- **BOM**: UTF-16 ByteOrderMark (0xFEFF)
- **UID**: application unique ID
- **UCNT**: application unique counter
- **PI**: pi 3.14...
- **ENP**: Euler's number e
- **RAND**: random number

---

## Flow Instructions in CODE

### Conditional
```c
#IF(°cond);
    // code if true
#ELSE;                    // optional
    // code if false
#END;
```

**OTIF Variant** (Or Then IF):
```c
#ELSE_OTIF(°newCond);     // additional condition after first #IF
```

### Loop
```c
#WHILE(°cond);
    // #SKIP;             // equivalent to continue
    // #BREAK;            // equivalent to break
#END;
```

---

## Coding Examples

### [001] Comments
```c
!!! Comment until first semicolon;
!! Normal comment;
```

### [002] Statement Separation
```c
!!Semicolon separates executive elements;
```

### [003-004] Strings and Literals
```c
"string with spaces";
£singleWord;              // equivalent to "singleWord"
```

### [005] Concatenation
```c
"my".."home".."my"++"home";  // "my home myhome"
```

### [006] Numeric Constants
```c
12;                       // decimal
0xC;                      // hexadecimal
0b1100;                   // binary
12.5;                     // float
```

### [007-008] Temporary Variables
```c
°a=10;                    // LTV - local
°b°=20;                   // GTV - global to thread
```

### [010] Assignments
```c
°a=10;                    // left assignment
10->°b;                   // right assignment
```

### [011] Atomic Assignments
```c
°a=5;
°a+=1;                    // °a becomes 6 (atomic)
°b=°a+=2*3;              // °a incremented by 2, then multiplied by 3
```

### [012-013] Boolean Tests
```c
°a=1; °b=0;
tstX(°a)..tstX(°b);      // "TRUE FALSE"

°a=£; °b="home"; °c=3;
~°a..~°b..~°c..~°d;      // "0 1 1 0" (°d is NULL)
```

### [014] Comparison Operators
```c
°a=100; °b=100; °c=50; °d="alpha"; °e=£beta;
°a==°b..°a>°c..°d<°e..°d<°a..°c!=°d;  // "1 1 1 1 1"
```

### [015] IF Function
```c
°t=1; °f=3; °c=1;
°r1=if(°c, °t, °f);      // returns 1 (°t)
°c=0;
°r2=if(°c, °t, °f);      // returns 3 (°f)
```

### [016-017] Flow Control
```c
#if(°a);
    °b+=1;
#else;
    °b-=1;
#end;

°cnt=0; °i=0;
#while(°i+=1 <=10);
    #if(°i == 5); #skip; #end;
    °cnt+=1;
    #if(°i == 8); #break; #end;
#end;
```

### [018-029] Mathematical Operations
```c
// Basic operations
°r1=7+3;     // 10 - sum
°r2=7-3;     // 4 - subtraction  
°r3=7*3;     // 21 - multiplication
°r4=7/3;     // 2.333... - division
°r5=7//3;    // 2 - integer division
°r6=7 MOD 3; // 1 - modulo
°r7=7^3;     // 343 - power
°r8=sqrt(25); // 5 - square root

// Mathematical functions
°r1=abs(-121);           // 121 - absolute value
°r2=flt(7/3,1);         // 2.3 - limit decimals

// Constants
PI;                      // 3.141592653589793
ENP;                     // 2.718281828459045

// Logarithms
°x=ENP^3; °y=log(°x);   // natural logarithm
°r1=log10(5); °r2=10^°r1; // base 10 logarithm

// Base conversions
12..Hex(12)..BIN(12);    // "12 0xc 0b1100"
```

### [025-028] Binary Operations
```c
// Bit-wise operations
145 & 28;                // binary AND
145 | 28;                // binary OR  
145 % 28;                // binary XOR

// Shift
182<<5;                  // left shift
182>>5;                  // right shift

// Bit field manipulation
BITF(182,5,2);          // read 2 bits from position 5
BITF(182,5,2,3);        // write 3 in 2 bits from position 5

// Byte swap
SWAP(0x12,£BYTE);       // byte swap
SWAP(0x1234,£WORD);     // word swap
SWAP(0x12345678,£DWORD); // double word swap
```

### [029-042] String Manipulation
```c
// Basic functions
len("bottle");           // 6 - length
fst("bottle");          // "b" - first character
lst("bottle");          // "e" - last character
fst("bottle",£A);       // "Aottle" - set first character
lst("bottle",£Z);       // "bottlZ" - set last character

// Spaces
nsp(" my length is ");   // "my length is" - remove spaces

// Case
UPR("big Hello");        // "BIG HELLO"
LWR("BIG HELLO");        // "big hello"

// Character conversions
CHAR(97);                // "a" - from code to character
CHARCOD("e");           // 101 - from character to code

// Extraction and modification
MID("Hello, how are you?",8,3);        // "how"
MID("Hello, how are you?",8,3,£who);   // "Hello, who are you?"

// Division
SPLT("Hello, how are you?",",",£LEFT);  // "Hello"
SPLT("Hello, how are you?",",",£RIGHT); // " how are you?"

// Search and replacement
SRCH("abcdefghijklmnopqrstuvwxyz","b"); // 2
SYMB_RPLC("abcdefghijklmnopqrstuvwxyz","b","[B]"); // "a[B]cdefghijklmnopqrstuvwxyz"

// Formatting
FRMT("%5d",52);          // "   52"
FRMT("%05d",52);         // "00052"
FRMT("%.1f",34.222222);  // "34.2"

// String shift
"problem"<<2;            // "oblem" - remove 2 characters from left
"problem">>3;            // "prob" - remove 3 characters from right

// Comparison
CMP("hello"," hello");   // 1 - precise comparison
MTCH("hello"," tello");  // 750 - statistical similarity

// NULL handling
NNL(NULL);               // "" - empty string if NULL
NNLv(NULL,£default);     // "default" - default value if NULL
```

### [043-045] Time and Output
```c
// Time
°start=tmr;
sleep(2000);             // wait 2 seconds
°stop=tmr;
°delay=°stop-°start;     // elapsed time

°ms=TMR;                 // milliseconds since startup
°sec=CLOCK;              // seconds since 1/1/1970

// Console output
chatput("Hello world!"); // write to PWK console
```

---

## BASKET

It's possible to save POWER-KI code elements (ITEMs) in files with **.bsk** extension to reuse or transfer them.

---

## Multi Threading

POWER-KI is designed for extensive multi-threading use. All functions are **thread safe** by default.

### SMF (Semaphores)
SMF allows serialization of THREAD activity.

**Characteristics**:
- 255 global semaphores (1-255) usable by ID number
- Semaphores created with SMF function use pointers
- Use of object PTR semaphores
- **Rule**: locked as many times (£LCKS), unlocked as many times (£LCKR)

**Available Information**:
- Semaphore status
- THREAD that holds it
- Lock line number
- Number of waiting threads (WAIT)
- Fast DEADLOCK resolution

### DOOR (Doors)
Solution to SMF limitations. DOORs can be unlocked by any thread that has the key.

**Characteristics**:
- System only
- 255 available doors (1-255)
- Key-based operation
- Access: "whoever has the key..."

---

## GUI and Native Cloud

### Native Cloud (NC) Characteristics
Important POWER-KI feature: **decoupling** between GUI graphic interface and generator code.

**Advantages over WEB solutions**:
- Better performance
- Less development time
- Native appearance
- Greater security

### Implementation
1. **Design**: GUI Editor creates page (.pki)
2. **Referencing**: page referenced in ASSEMBLY in GUI ITEM
3. **Interaction**: modify GUI elements as if they were local
4. **Events**: GUI changes reflected in ASSEMBLY
5. **SIGNAL**: event association with code actions

### Operation
- GUI can run on different machine
- Appearance and functionality as if local
- Event handling (mouse, page movements)
- Action programming through SIGNALs

---

*Complete documentation of POWER-KI (PWK) programming language - © XPLAB Research in Automation*