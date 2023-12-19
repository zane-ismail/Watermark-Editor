SELECT people.name FROM people JOIN directors ON people.id= directors.person_id JOIN movies ON directors.movies_id= movies.id WHERE movies.title = " Toy Story";
