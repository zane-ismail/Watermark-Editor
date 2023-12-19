SELECT DISTINCT people.name FROM people JOIN stars ON people.id= stars.person_id JOIN movies ON stars.movies.id WHERE movies.year = 2012 ORDER BY people.birth;


