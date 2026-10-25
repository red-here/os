#!/bin/bash

FILE="address_book.txt"

create_book() {
    echo "Name,Phone,Email" > "$FILE"
    echo "Address book created."
}

view_book() {
    if [ -f "$FILE" ]; then
        cat "$FILE"
    else
        echo "Address book does not exist."
    fi
}

insert_record() {
    if [ ! -f "$FILE" ]; then
        create_book
    fi

    read -p "Enter name: " name
    read -p "Enter phone: " phone
    read -p "Enter email: " email

    echo "$name,$phone,$email" >> "$FILE"
    echo "Record inserted."
}

delete_record() {
    read -p "Enter name to delete: " name

    grep -v "^$name," "$FILE" > temp.txt
    mv temp.txt "$FILE"

    echo "Record deleted."
}


modify_record() {
    read -p "Enter name to modify: " old

    if grep -q "^$old," "$FILE"; then
        read -p "Enter new name: " name
        read -p "Enter new phone: " phone
        read -p "Enter new email: " email

        grep -v "^$old," "$FILE" > temp.txt
        echo "$name,$phone,$email" >> temp.txt
        mv temp.txt "$FILE"

        echo "Record modified."
    else
        echo "Record not found."
    fi
}


while true
do
    echo
    echo "1. Create address book"
    echo "2. View address book"
    echo "3. Insert record"
    echo "4. Delete record"
    echo "5. Modify record"
    echo "6. Exit"

    read -p "Enter your choice: " choice

    case $choice in
        1) create_book ;;
        2) view_book ;;
        3) insert_record ;;
        4) delete_record ;;
        5) modify_record ;;
        6) echo "Goodbye"; exit ;;
        *) echo "Invalid choice" ;;
    esac
done
