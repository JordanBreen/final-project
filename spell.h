typedef struct spell {
//type - identifier ------------ storage
  char * name;                // string
  char * school;              // enum
  char * subschool;           // enum
  char * descriptor;          // enum
  char * spell_level;         // ptr array to 'classes'
  char * casting_time;        // struct
  char * components;          // flag
  char * costly_component;    // bool 1
  char * range;               // struct
  char * area;                // struct
  char * effect;              // struct
  char * targets;             // struct
  char * duration;            // struct
  char * dismissible;         // bool 2
  char * shapeable;           // bool 3
  char * saving_throw;        // struct
  char * spell_resistance;    // bool 4
  char * description;         // string
  char * description_formated // string





} Spell;

/*
typedef enum school {
  PLACE_HOLDER
} School;
*/
