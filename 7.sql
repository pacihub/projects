SELECT title, rating FROM movies 
JOIN ratings ON ratings.movie_id = movies.id 

WHERE movies.year = "2010" and ratings.rating IS NOT NULL
ORDER BY ratings.rating DESC, title ASC;

/* groups first by rating and then title is alphabetical

