#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <time.h>
#include "spell.h"
#include "thread.h"
#include "bit_def.h"

static const byte NUM_THREADS = 4;
spell_id   spell_ids_to_load[] = {1, 5, 10, 15, 20};
size_t     num_spell_ids_to_load = sizeof(spell_ids_to_load) / sizeof(*spell_ids_to_load);
spell    **loaded_spells;
size_t     num_loaded_spells = sizeof(spell_ids_to_load) / sizeof(*spell_ids_to_load);
int main()
{
  init_resources(NUM_THREADS);

  load_spells(NUM_THREADS, spell_ids_to_load, num_spell_ids_to_load, &loaded_spells);
  print_spells(loaded_spells, num_loaded_spells);

  free_resources(NUM_THREADS);
  return 0;
}
