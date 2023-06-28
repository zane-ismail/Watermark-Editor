import csv
import sys


def main():

    # TODO: Check for command-line usage
    # First command-line argument the name of a CSV file
    database = sys.argv[1]

    # Second command-line argument the name of a text file
    sequences = sys.argv[2]

    # if the incorrect number of command-line arguments print an error message
    if len(sys.argv) != 3:
        print("Incorrect input ")

    # TODO: Read database file into a variable
    # open the CSV file and read its contents into memory
    list = []
    with open(database) as file:
        db_reader = csv.DictReader(file)
        for row in db_reader:
            print(row)


    # TODO: Read DNA sequence file into a variable
    with open(sequences) as f:
        s_reader = f.read()
        print(s_reader)


    # TODO: Find longest match of each STR in DNA sequence
    # seq_list = []
    # for i in range(len(s_reader)):
    #     if s_reader[i] == "A" and s_reader[i+1] == "G":


    # TODO: Check database for matching profiles

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
