-- Keep a log of any SQL queries you execute as you solve the mystery.

--Find crime report
SELECT * FROM crime_scene_reports
WHERE year = 2021 AND month = 7 AND day = 28 AND street = "Humphrey Street" AND description LIKE "%duck%";

--Find the 3 transcripts of incidents
SELECT * FROM interviews WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE "%bakery%";

--Look at bakery_security_logs for cars that left the parking lot within 10 mins of theft
SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25;

--Look at atm_transactions in the morning before the theft for someone Eugene recognised
SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28;

--Look at phone_calls lasting less than a minute around the time of the theft
SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60;

--Look at destination city from earliest flight from fiftyville on 29/07/2021
SELECT city FROM airports WHERE id IN
(SELECT destination_airport_id FROM flights WHERE year = 2021 AND month = 7 AND day = 29 AND origin_airport_id IN
(SELECT ID FROM airports WHERE city = "Fiftyville") ORDER BY flights.hour) LIMIT 1;

-- Look for passport_number from that booking
SELECT passport_number FROM passengers WHERE flight_id =
(SELECT id FROM flights WHERE year = 2021 AND month = 7 AND day = 29 AND origin_airport_id IN
(SELECT ID FROM airports WHERE city = "Fiftyville"));

--Find person with matching licence_plate, account_number and caller from people
SELECT name FROM people WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs WHERE
year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25
) AND phone_number IN
(SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60)
AND passport_number IN
(SELECT passport_number FROM passengers WHERE flight_id =
(SELECT id FROM flights WHERE year = 2021 AND month = 7 AND day = 29 AND origin_airport_id IN
(SELECT ID FROM airports WHERE city = "Fiftyville")));

-- Find the accomplice
SELECT caller FROM phone_calls WHERE caller =
(SELECT name FROM people WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs WHERE
year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25
) AND phone_number IN
(SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60)
AND passport_number IN
(SELECT passport_number FROM passengers WHERE flight_id =
(SELECT id FROM flights WHERE year = 2021 AND month = 7 AND day = 29 AND origin_airport_id IN
(SELECT ID FROM airports WHERE city = "Fiftyville"))))
AND year = 2021 AND month = 7 AND day = 28 AND duration < 60;
