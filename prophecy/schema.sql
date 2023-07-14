CREATE TABLE assignments (
    id INTEGER NOT NULL,
    student_id INTEGER NOT NULL,
    house_id INTEGER NOT NULL,
    PRIMARY KEY(id)
);

Create TABLE houses (
    id INTEGER NOT NULL,
    house_name TEXT NOT NULL,
    head TEXT NOT NULL,
    PRIMARY KEY(id)
);

CREATE TABLE students (
    id INTEGER NOT NULL,
    student_name TEXT NOT NULL,
    house TEXT NOT NULL,
    head TEXT NOT NULL,
    PRIMARY KEY(id)
);

EXEC sp_rename 'students', 's';
ALTER TABLE 'students' RENAME TO 's';