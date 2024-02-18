# List of all the board related files.
BOARDSRC = $(CHIBIOS)/os/hal/boards/AT_START144_F437ZM/board.c

# Required include directories
BOARDINC = $(CHIBIOS)/os/hal/boards/AT_START144_F437ZM

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
