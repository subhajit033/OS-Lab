#!/bin/bash

# Prompt the user to create a file
read -p "Enter the name of the file you want to create: " filename

# Create the file
touch "$filename"

# Display the default permissions of the file
echo "Default file permissions of '$filename':"
ls -l "$filename"

# Menu options to change file permissions
echo "Choose an option to change file permissions:"
echo "1) User has all permissions, group has read and write, others have read."
echo "2) User has exactly all permissions."
echo "3) User, group, and others have all permissions."
read -p "Enter your choice (1, 2, or 3): " choice

# Change permissions based on user choice

case $choice in
    1)
        chmod u=rwx,g=rw,o=r "$filename"
        echo "Permissions changed to: User has all permissions, group has read and write, others have read."
        ;;
    2)
        chmod u=rwx "$filename"
        echo "Permissions changed to: User has exactly all permissions."
        ;;
    3)
        chmod u=rwx,g=rwx,o=rwx "$filename"
        echo "Permissions changed to: User, group, and others have all permissions."
        ;;
    *)
        echo "Invalid choice, please enter 1, 2, or 3."
        exit 1
        ;;
esac

# Display the updated file permissions
echo "Updated file permissions of '$filename':"
ls -l "$filename"
