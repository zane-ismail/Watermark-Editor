import csv
import requests


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    states_list = []
    new_cases = {}
    previous_cases = {}
    # read through csv file
    for row in reader:
        # add states to a list
        while row["state"] not in states_list:
            states_list.append(row["state"])
            new_cases.update({row["state"]: []})
        # iterate through states and add them to a new dictionary
        for state in states_list:
            new_case = {"State": row["state"], "Cases": int(row["cases"]), "Date": row["date"]}
            # If states match
            if state == new_case['State']:

                # Once cases reach 14, Delete the first entry
                if len(new_cases[state]) > 13:
                    # print(len(new_cases[state]) - 1)
                    new_cases[state].pop(0)

                last_entry = len(new_cases[state]) - 1
                # If there's no cases, add the first entry
                if last_entry < 0:
                    new_cases[state].append(new_case["Cases"])
                else:
                    if new_case["Cases"] == new_cases[state][last_entry]:
                        new_cases[state].append(0)
                    else:
                        x = new_case["Cases"]
                        for i in range(last_entry + 1):
                            x = x - new_cases[state][i]
                        new_cases[state].append(x)
    return new_cases


# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):
    for state in states:
        day = 6
        avg = 0
        prev_avg = 0
        for i in range(6):
            avg = avg + new_cases[state][day]
            day += 1
        avgs = (round(avg / 7))
        # previous_days
        for i in range(6):
            prev_avg = prev_avg + new_cases[state][i]
        prev_avgs = (round(prev_avg / 7))
    if prev_avgs > avgs:
        rate = "a decrease"
    else:
        rate = "an increase"

    print(avgs)
    print(prev_avgs)
    print(f"{state} has a 7-day average of {avgs} and {rate} of {(avgs - prev_avgs) / prev_avgs} %")
    return


main()
