select title , rating from movies inner join ratings on id = movie_id where movies.year = 2010 order by rating DESC, title ASC;