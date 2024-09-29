DROP DATABASE IF EXISTS exerciseDB;
CREATE DATABASE exerciseDB;

USE exerciseDB;

CREATE TABLE player (
    player_id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(50) NOT NULL,
    password VARCHAR(100) NOT NULL
);

CREATE TABLE match (
    match_id INT AUTO_INCREMENT PRIMARY KEY,
    match_identifier VARCHAR(50) NOT NULL,
    duration TIME NOT NULL,
    winner_id INT,  -- ID of the winner
    FOREIGN KEY (winner_id) REFERENCES player(player_id)
);

CREATE TABLE player_match (
    player_id INT,
    match_id INT,
    PRIMARY KEY (player_id, match_id),
    FOREIGN KEY (player_id) REFERENCES player(player_id),
    FOREIGN KEY (match_id) REFERENCES match(match_id)
);

INSERT INTO player (username, password) VALUES ('player1', 'contra1');
INSERT INTO player (username, password) VALUES ('player2', 'contra2');
INSERT INTO player (username, password) VALUES ('player3', 'contra3');

INSERT INTO match (match_identifier, duration, winner_id)
VALUES ('Match 1', '00:30:00', 1);

INSERT INTO match (match_identifier, duration, winner_id)
VALUES ('Match 2', '00:45:00', 2);

INSERT INTO player_match (player_id, match_id) VALUES (1, 1);
INSERT INTO player_match (player_id, match_id) VALUES (2, 1);
INSERT INTO player_match (player_id, match_id) VALUES (2, 2);
INSERT INTO player_match (player_id, match_id) VALUES (3, 2);
