-- For see the tables
.table

-- For see the db creation command
.schema

-- For see all of crime_scene_reports table to see overview data volume
SELECT * FROM crime_scene_reports;

-- Reduce the search area
SELECT * FROM crime_scene_reports WHERE street = "Humphrey Street";

-- Reduce the search time range
SELECT * FROM crime_scene_reports WHERE street = "Humphrey Street" and year = 2021 and month = 7 and day = 28;


SELECT id,description FROM crime_scene_reports WHERE street = "Humphrey Street" and year = 2021 and month = 7 and day = 28;
--> Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.

-- For see all of interviews table to over view data volume
SELECT id,name,transcript FROM interviews WHERE year = 2021 and month = 7 and day = 28;
SELECT transcript FROM interviews WHERE year = 2021 and month = 7 and day = 28;
--> Interviews related to the crime scene:
-- 1. Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
-- 2. I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
-- 3. As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

SELECT id,minute,activity,license_plate FROM bakery_security_logs
WHERE year = 2021 and month = 7 and day = 28 and hour = 10 and minute>=15 and minute<=25 and activity = "exit";
-- Those who left the bakery about 10 minutes after the robbery:
-- +-----+--------+----------+---------------+
-- | id  | minute | activity | license_plate |
-- +-----+--------+----------+---------------+
-- | 260 | 16     | exit     | 5P2BI95       |
-- | 261 | 18     | exit     | 94KL13X       |
-- | 262 | 18     | exit     | 6P58WS2       |
-- | 263 | 19     | exit     | 4328GD8       |
-- | 264 | 20     | exit     | G412CB7       |
-- | 265 | 21     | exit     | L93JTIZ       |
-- | 266 | 23     | exit     | 322W7JE       |
-- | 267 | 23     | exit     | 0NTHK55       |
-- +-----+--------+----------+---------------+
--> suspect license_plate: 5P2BI95, 94KL13X, 6P58WS2, 4328GD8, G412CB7, L93JTIZ, 322W7JE, 0NTHK55

SELECT * FROM people
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE year = 2021 and month = 7 and day = 28 and hour = 10 and minute >= 15 and minute <= 25 and activity = "exit";
-- +--------+---------+----------------+-----------------+---------------+
-- |   id   |  name   |  phone_number  | passport_number | license_plate |
-- +--------+---------+----------------+-----------------+---------------+
-- | 221103 | Vanessa | (725) 555-4692 | 2963008352      | 5P2BI95       |
-- | 243696 | Barry   | (301) 555-4174 | 7526138472      | 6P58WS2       |
-- | 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
-- | 398010 | Sofia   | (130) 555-0289 | 1695452385      | G412CB7       |
-- | 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
-- | 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
-- | 560886 | Kelsey  | (499) 555-9472 | 8294398571      | 0NTHK55       |
-- | 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
-- +--------+---------+----------------+-----------------+---------------+
--> suspect persons(with leaving time): Vanessa, Barry , Iman , Sofia , Luca , Diana  , Kelsey , Bruce

SELECT people.id, name, phone_number, passport_number, license_plate , bank_accounts.account_number, amount FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE year = 2021 and month = 7 and day = 28 and atm_location = "Leggett Street" and transaction_type = "withdraw";
-- +--------+---------+----------------+-----------------+---------------+----------------+--------+
-- |   id   |  name   |  phone_number  | passport_number | license_plate | account_number | amount |
-- +--------+---------+----------------+-----------------+---------------+----------------+--------+
-- | 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       | 49610011       | 50     |
-- | 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       | 26013199       | 35     |
-- | 458378 | Brooke  | (122) 555-4581 | 4408372428      | QX4YZN3       | 16153065       | 80     |
-- | 395717 | Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       | 28296815       | 20     |
-- | 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       | 25506511       | 20     |
-- | 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       | 28500762       | 48     |
-- | 449774 | Taylor  | (286) 555-6063 | 1988161715      | 1106N58       | 76054385       | 60     |
-- | 438727 | Benista | (338) 555-6650 | 9586786673      | 8X428L0       | 81061156       | 30     |
-- +--------+---------+----------------+-----------------+---------------+----------------+--------+
--> suspect persons(with transactions place): Vanessa, Barry , Iman , Sofia , Luca , Diana  , Kelsey , Bruce

SELECT name FROM people
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE atm_transactions.year = 2021 and atm_transactions.month = 7 and atm_transactions.day = 28 and atm_location = "Leggett Street" and transaction_type = "withdraw"
and hour = 10 and minute >= 15 and minute <= 25 and activity = "exit";
-- +-------+
-- | name  |
-- +-------+
-- | Bruce |
-- | Diana |
-- | Iman  |
-- | Luca  |
-- +-------+
--   _  suspect persons(with leaving time): Bruce, Diana, Brooke, Kenny, Iman, Luca, Taylor, Benista
--      suspect persons(with transactions place): Vanessa, Barry , Iman , Sofia , Luca , Diana  , Kelsey , Bruce
---------------------------------------------------------------------------------------
-->     suspect persons(1): Bruce, Diana, Iman, Luca


SELECT name, caller, receiver FROM people
JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE year = 2021 and month = 7 and day = 28 and duration < 60;
-- +---------+----------------+----------------+
-- |  name   |     caller     |    receiver    |
-- +---------+----------------+----------------+
-- | Sofia   | (130) 555-0289 | (996) 555-8899 |
-- | Kelsey  | (499) 555-9472 | (892) 555-8872 |
-- | Bruce   | (367) 555-5533 | (375) 555-8161 |
-- | Kelsey  | (499) 555-9472 | (717) 555-1342 |
-- | Taylor  | (286) 555-6063 | (676) 555-6554 |
-- | Diana   | (770) 555-1861 | (725) 555-3243 |
-- | Carina  | (031) 555-6622 | (910) 555-3251 |
-- | Kenny   | (826) 555-1652 | (066) 555-9701 |
-- | Benista | (338) 555-6650 | (704) 555-2131 |
-- +---------+----------------+----------------+
-- suspect persons(whit phone_number): Sofia, Kelsey, Bruce, Kelsey, Taylor, Diana, Carina, Kenny, Benista


SELECT people.id, name, phone_number, flight_id, people.passport_number FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
where flight_id in (
    select id from flights
    where origin_airport_id in (
        select id from airports
        where airports.city = "Fiftyville"
    )
    and year = 2021 and month = 7 and day = 29  ORDER BY hour , minute LIMIT 1
);
-- +--------+--------+----------------+-----------+-----------------+
-- |   id   |  name  |  phone_number  | flight_id | passport_number |
-- +--------+--------+----------------+-----------+-----------------+
-- | 953679 | Doris  | (066) 555-9701 | 36        | 7214083635      |
-- | 398010 | Sofia  | (130) 555-0289 | 36        | 1695452385      |
-- | 686048 | Bruce  | (367) 555-5533 | 36        | 5773159633      |
-- | 651714 | Edward | (328) 555-1152 | 36        | 1540955065      |
-- | 560886 | Kelsey | (499) 555-9472 | 36        | 8294398571      |
-- | 449774 | Taylor | (286) 555-6063 | 36        | 1988161715      |
-- | 395717 | Kenny  | (826) 555-1652 | 36        | 9878712108      |
-- | 467400 | Luca   | (389) 555-5198 | 36        | 8496433585      |
-- +--------+--------+----------------+-----------+-----------------+
-->  suspect persons(with flight imformation): Doris, Sofia, Bruce, Edward, Kelsey, Taylor, Kenny, Luca
--   suspect persons(1): Bruce, Diana, Iman, Luca
-------------------------------------------------------
--   suspect persons(2): Bruce , Luca
--   suspect persons(whit phone_number): Sofia, Kelsey, Bruce, Kelsey, Taylor, Diana, Carina, Kenny, Benista
-------------------------------------------------------

--========>  The thief = Bruce
--++++++++>  flight_id = 36

select name from people
join phone_calls on phone_number = receiver
where caller = (
    select phone_number from people
    where name = "Bruce"
)
and year = 2021 and month = 7 and day = 28 and duration < 60;
-- +-------+
-- | name  |
-- +-------+
-- | Robin |
-- +-------+

select city from airports
where airports.id = (
    select destination_airport_id from flights
    where id = 36
);
-- +---------------+
-- | New York City |
-- +---------------+
