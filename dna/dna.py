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
    csv_list = []
    with open(database) as csvfile:
        str_csv = csv.DictReader(csvfile)
        for row in str_csv:
            csv_list.append(row)

    # TODO: Read DNA sequence file into a variable
    with open(sequences) as file:
        str_txt = file.read()
        txt_list = str_txt

    # TODO: Find longest match of each STR in DNA sequence
    str_dict = {"AGATC": 0, "TTTTTTCT": 0, "AATG": 0, "TCTAG": 0, "GATA": 0, "TATC": 0, "GAAA": 0, "TCTG": 0}

    for seq in str_dict:
        str_dict[seq] = longest_match(txt_list, seq)

    # TODO: Check database for matching profiles
    matches = {
    }

    for row in csv_list:
        matches.update({row["name"]: 0})

    for i in str_dict:
        with open(database) as csvfile:
            str_csv = csv.DictReader(csvfile)
            try:
                for row in str_csv:
                    if str_dict[i] == int(row[i]):
                        matches[row["name"]] += 1
                        if matches[row["name"]] == len(row) - 1:
                            print(row["name"])
                            return
            except KeyError:
                pass

    print("No match")
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
