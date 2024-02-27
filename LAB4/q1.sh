
#!/bin/bash
original_file="$1"
# Create a backup file with a '.bak' extension
backup_file="${original_file}.bak"
cp "$original_file" "$backup_file"
