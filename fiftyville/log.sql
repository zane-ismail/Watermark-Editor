-- Keep a log of any SQL queries you execute as you solve the mystery.

--Find crime report
SELECT * FROM crime_scene_reports
WHERE year = 2021 AND month = 7 AND day = 28 AND street = "Humphrey Street" AND description LIKE "%duck%";

--Find the 3 transcripts of incidents
SELECT * FROM interviews WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE "%bakery%";

--Look at bakery_security_logs for cars that left the parking lot within 10 mins of theft
SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25;

--Look at atm_transactions in the morning before the theft for someone Eugene recognised
SELECT

--Look at phone_calls lasting less than a minute around the time of the theft


--Look at flights for the earliest flight from fiftyville on 29/07/2021