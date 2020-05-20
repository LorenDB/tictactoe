#!/bin/bash
# This script builds the Tic-Tac-Toe program.

# Get some variables.
USERNAME=`whoami`
HAVECDED="no" # This tells us whether we have changed directories to build the program.
COMPILER="g++"
VERBOSE=
BUILDPATH="/home/$USERNAME/.local/bin" # default to user build
SUDO=
OUTNAME="ttt"

# This function will build the program.
build()
{
    echo "Compiler: $COMPILER"
    if [ -e "$BUILDPATH/$OUTNAME" ]; then
        $SUDO rm "$BUILDPATH/$OUTNAME"
    fi
    echo "Building TicTacToe.cpp..."
    $SUDO $COMPILER TicTacToe.cpp -o "$BUILDPATH/$OUTNAME" $VERBOSE
    if [ "$?" != 0 ]; then
        echo "Build error!"
        exit 1
    fi
    $SUDO chmod +x "$BUILDPATH/$OUTNAME"
}

print_help()
{
    echo "Build script for the Tic-Tac-Toe program."
    echo "Usage:"
    echo "  -b, --buildtype <type>      Specify how to build the program. Type \'user\'"
    echo "                              to build it for your user account only, and"
    echo "                              type \'system\' to install for all users. Note:"
    echo "                              a system build requires sudo priveliges. Defaults"
    echo "                              to user."
    echo "  -c, --compiler <compiler>   Specify the compiler to use. The script"
    echo "                              currently supports g++ and clang++."
    echo "  -h, --help                  Show this message."
    echo "  -o, --out <name>            Specify the name of the newly compiled program."
    echo "  -r, --remove                Remove the Tic-Tac-Toe program. If you have"
    echo "                              compiled the program with a non-default command"
    echo "                              name, you should specify the -o <name> option"
    echo "                              before the -r option."
    echo "  -u, --update                Update the Tic-Tac-Toe program."
    echo "  -v, --verbose               Show detailed information from the compiler"
    echo "                              about the build."
    echo
    echo "If the script fails, type \"\$?\" to get the exit code. Then"
    echo "read the script to find where that particular exit code is used."
}

uninstall_program()
{
    printf "Are you sure you want to remove the program? "
    read SHOULDPROCEED
    case "$SHOULDPROCEED" in
        "y")
            if [ -e "/bin/$OUTNAME" ]; then
                sudo rm "/bin/ttt"
            fi
            if [ -e "/home/$USERNAME/.local/bin/$OUTNAME" ]; then
                rm "/home/$USERNAME/.local/bin/$OUTNAME"
            fi
            ;;
        *)
            echo "Aborting."
            exit 0
            ;;
    esac
}

update_program()
{
    git clone "https://github.com/LorenDB/tictactoe.git/"
    FILES=`ls tictactoe`
    rm $FILES -f -r $VERBOSE
    cp "tictactoe/*.*" .
    rm -r "tictactoe"
}

# Our main function. This takes care of all operations.
main()
{
    # Parse args.
    while [ "$1" != "" ]; do
        case "$1" in
            -b|--buildtype)
                shift
                BUILDTYPE="$1"
                case "$BUILDTYPE" in
                    u|user)
                        BUILDPATH="/home/$USERNAME/.local/bin"
                        ;;
                    s|system)
                        BUILDPATH="/bin"
                        SUDO="sudo"
                        ;;
                    *)
                        echo "Invalid build type! Exiting..."
                        exit 2
                        ;;
                esac
                shift
                ;;
            -c|--compiler)
                shift
                COMPILER="$1"
                shift
                ;;
            -h|--help)
                print_help
                exit 0
                ;;
            -o|--out)
                shift
                OUTNAME="$1"
                shift
                ;;
            -r|--remove)
                uninstall_program
                exit 0
                ;;
            -u|--update)
                update_program
                shift
                ;;
            -v|--verbose)
                VERBOSE="-v"
                shift
                ;;
            *)
                shift
                ;;
        esac
    done

    # Build.
    build
}

# Run the script. $* passes parameters to main.
main $*
