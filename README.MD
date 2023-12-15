# SGR in C

## Quick intro to SGR
SGR is the new system for recycling PET bottles implemented in Romania, similar to other countries in the EU. It works by adding a deposit to the price of PET containers, which could be cashed out once the container is returned to one of the selected locations (usually in stores).

## Simple implementation in C
This project will be basic:
 
- a special .sgr file is read
- commands from the .sgr file are executed
- a simple result will be displayed

## SGR file structure
There is a basic dialect for SGR files:

`[COMMAND NAME] [PARAMS]\n`

For now, only a couple of commands will be added.

### Commands

`P_SET [PRICE]` - sets a new price for the deposit
`BUY [QUANTITY]` - buy a number of containers
`RETURN [QUANTITY]` - return a number of containers