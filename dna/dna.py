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
        # for row in db_reader:
        #     print(row)


    # TODO: Read DNA sequence file into a variable
    with open(sequences) as f:
        s_reader = f.read()
        # print(s_reader)


    # TODO: Find longest match of each STR in DNA sequence
    seq_list = {"AGATC": 1, "TTTTTTCT": 1, "AATG": 1, "TCTAG": 1, "GATA": 1, "TATC": 1, "GAAA": 1, "TCTG": 1}
    count = 0

    for i in range(len(s_reader)):
        # print(f"length:{len(s_reader)}")
        for j in range(len(s_reader)):
            for k in seq_list:
                if s_reader[i:j] == k:
                    # print(f"MATCH{seq_list[k]}")
                    if s_reader[i+len(s_reader[i:j]):j+len(s_reader[i:j])] == s_reader[i:j]:
                        # print(s_reader[i+len(s_reader[i:j]):j+len(s_reader[i:j])])
                        seq_list[s_reader[i:j]] +=1

                        # print(f"j: {j}")
                        # print(f"i: {i}")
                        # if i + j == len(s_reader) - 1:
                        #     # seq_list[s_reader[i:j]] +=1
                        # print(f"SEQ LIST: {seq_list}")
                        #     print(f"AAAAAA:{seq_list[s_reader[i:j]]}")
                        #     print("\n")


    # TODO: Check database for matching profiles
    # for k in seq_list:
    #     print(k)
        # for row in db_reader:
        #     row[k] = int(row[k])
        #     if k == row[k]:
        #         print(f"ROWK: {row[k]}")
        #         print("MATCH!")

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
