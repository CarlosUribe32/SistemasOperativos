#ifndef PERSON_H_
#define PERSON_H_

// Forward declaration
struct person_t;

// Memory allocator
struct person_t* person_new();

// Constructor
void person_ctor(struct person_t*,
const char* /* first name */,
const char* /* last name */,
unsigned int /* birth year */);

// Destructor
void person_dtor(struct person_t*);

// Behavior functions
void person_get_first_name(struct person_t*, char*);
void person_get_last_name(struct person_t*, char*);
unsigned int person_get_birth_year(struct person_t*);

#endif /* PERSON_H_ */  