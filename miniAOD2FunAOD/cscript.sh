#!/bin/bash

#=====================================================#
#  Bash script to make C/C++ scripts with predefined  #
#  functions and comments.                            #
#=====================================================#


# Prompt the user to enter the filename

echo "Enter the program name: "
read FILE

# Prompt the user about the author

echo "Enter the name of the author: "
read AUTHOR

# Prompt user for any additional comments
echo "Enter any additional comments to be added in the beginning: "
read INITIAL_COMMENT

FILENAME="$FILE".cc

# Check if filename already exists

if [ -e $FILENAME ];
then
    echo "Error creating file. ${FILENAME} already exists!"
    exit 1
fi

touch ${FILENAME}

CURRENT_DATE=$(date +"%d %B %Y")

echo //-----------------------------------------------------  > $FILENAME
echo // ${INITIAL_COMMENT}                                   >> $FILENAME
echo // Original Author: ${AUTHOR}                           >> $FILENAME
echo // Date Created: ${CURRENT_DATE}                        >> $FILENAME
echo // C/C++ Source Code                                    >> $FILENAME
echo //----------------------------------------------------- >> $FILENAME


cat <<EOF >> $FILENAME

//---------------------------------
// system include files
//---------------------------------

//---------------------------------
// user include files
//---------------------------------

//---------------------------------
// Class Declaration
//---------------------------------

//---------------------------------
// user defined functions
//---------------------------------


EOF

chmod +x "$FILENAME"

# Moving the file to the required directory

mv "$FILENAME" "src"

# Closing Log / Messages

echo "$FILENAME has been successfully created and moved to /src !"


