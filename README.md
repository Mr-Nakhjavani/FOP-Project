# Monster - A Simple Version Control System

Monster is a lightweight version control system (VCS) inspired by Git. It provides basic functionality for tracking changes in your files, committing them, branching, tagging, and more. monster is designed to be simple and easy to use, making it a great tool for small projects or learning how version control systems work.

---

## Features

- Initialize a Repository: Create a new monster repository to start tracking changes.
- Track Changes: Add files to the staging area and commit them.
- Branching: Create and switch between branches to manage different lines of development.
- Tagging: Mark specific points in your project's history with tags.
- Logs: View the commit history and filter by branch, author, or message.
- Checkout: Switch between commits, branches, or tags.
- Grep: Search for specific content in files across commits.
- Undo Changes: Reset or undo changes in the staging area.

---

## Installation

monster is written in C and can be compiled on any system with a C compiler (e.g., GCC).

### Prerequisites
- GCC (GNU Compiler Collection)
- Windows (for Windows-specific functions like SetCurrentDirectory)

### Steps
1. Clone the repository or download the source code.
      git clone https://github.com/Mr-Nakhjavani/FOP-Project.git
   cd monster
   
2. Compile the code using GCC.
      gcc monster.c -o monster
   
3. Run the executable.
      ./monster
   

---

## Usage

### Commands

#### Initialize a Repository
monster init
Initializes a new monster repository in the current directory.

#### Configure User Information
monster config -global user.name "Your Name"
monster config -global user.email "your.email@example.com"
Sets the user's name and email for commits.

#### Add Files to Staging Area
monster add <file1> <file2>
Adds files to the staging area for the next commit.

#### Commit Changes
monster commit -m "Your commit message"
Commits the changes in the staging area with a message.

#### View Status
monster status
Shows the status of files in the working directory and staging area.

#### Create a Branch
monster branch <branch_name>
Creates a new branch.

#### Switch to a Branch or Commit
monster checkout <branch_name_or_commit_id>
Switches to the specified branch or commit.

#### View Commit History
monster log
Displays the commit history.

#### Create a Tag
monster tag <tag_name> -m "Tag message"
Creates a tag at the current commit.

#### Search in Files
monster grep <file> <word>
Searches for a specific word in a file.

#### Reset Changes
monster reset <file>
Removes a file from the staging area.

#### Undo Last Add
monster reset -undo
Undoes the last add operation.

---

## Example Workflow

1. Initialize a repository:
      monster init
   

2. Add files to the staging area:
      monster add file1.txt file2.txt
   

3. Commit the changes:
      monster commit -m "Initial commit"
   

4. Create a new branch:
      monster branch feature-branch
   

5. Switch to the new branch:
      monster checkout feature-branch
   

6. Make changes and commit them:
      monster add file3.txt
   monster commit -m "Added file3.txt"
   

7. View the commit history:
      monster log
   

8. Create a tag:
      monster tag v1.0 -m "First release"
   

9. Search for a word in a file:
      monster grep file1.txt "search_word"
   

---

## File Structure

- monster/: The hidden directory where monster stores its data.
  - configname.txt: Stores the user's name.
  - configmail.txt: Stores the user's email.
  - staging area.txt: Tracks files in the staging area.
  - commit history.txt: Stores the commit history.
  - tags.txt: Stores tag information.
  - branches/: Contains branch-specific data.
  - commits/: Stores commit snapshots.
  - staging/: Tracks staged files.

---

## Limitations

- monster is a simple VCS and does not support advanced features like merging, rebasing, or remote repositories.
- It is currently designed for Windows due to the use of Windows-specific functions like SetCurrentDirectory.

---

## Contributing

Contributions are welcome! If you'd like to improve monster, feel free to open an issue or submit a pull request.

---

## License
