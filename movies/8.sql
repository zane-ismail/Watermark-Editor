
    Your query should output a table with a single column for the name of each person.
    You may assume that there is only one movie in the database with the title Toy Story.
SELECT people.name FROM people JOIN directors ON people.id= directors.person_id JOIN movies ON directors.movie_id= movies.id WHERE movies.title = " Toy Story";
