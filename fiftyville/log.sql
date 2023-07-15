-- Keep a log of any SQL queries you execute as you solve the mystery.

--Find crime report
SELECT * FROM crime_scene_reports
WHERE year = 2021 AND month = 7 AND day = 28 AND street = "Humphrey Street" AND description LIKE "%duck%";

--Find the 3 transcripts of incidents
SELECT * FROM interviews WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE "%bakery%";

--Look at bakery_security_logs for cars that left the parking lot within 10 mins of theft


--Look at atm_transactions in the morning before the theft for someone Eugene recognised


--Look at phone_calls after the 