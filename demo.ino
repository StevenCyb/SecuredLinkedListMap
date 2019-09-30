#include "src/SecuredLinkedListMap.h"

SecuredLinkedListMap<String, String> stringMap = SecuredLinkedListMap<String, String>();
SecuredLinkedListMap<String, int> *intMap = new SecuredLinkedListMap<String, int>();

void setup() {
  Serial.begin(115200);
  while(!Serial){}

  stringMap.put("Sarah", "Femal");
  stringMap.put("Alex", "Male");
  stringMap.put("Dilara", "Femal");
  stringMap.put("Steven", "Male");
  intMap->put("Sarah", 161);
  intMap->put("Alex", 190);
  intMap->put("Dilara", 166);
  intMap->put("Steven", 180);
  // stringMap = {"Sarah": "Femal", "Alex": "Male", "Dilara": "Femal", "Steven": "Male"}
  // intMap = {"Sarah": 161, "Alex": 190, "Dilara": 166, "Steven": 180}

  Serial.println(stringMap.size()); // -> 4
  Serial.println(intMap->size());   // -> 4

  Serial.println(stringMap.has("Sarah")); // -> 1 (True)
  Serial.println(intMap->has("Sarah"));   // -> 1 (True)
  Serial.println(stringMap.has("Tim"));   // -> 0 (False)
  Serial.println(intMap->has("Tim"));     // -> 0 (False)

  stringMap.remove("Steven");
  intMap->remove("Steven");
  // stringMap = {"Sarah": "Femal", "Alex": "Male", "Dilara": "Femal"}
  // intMap = {"Sarah": 161, "Alex": 190, "Dilara": 166}

  Serial.println(stringMap.get("Dilara")); // -> Femal
  Serial.println(intMap->get("Dilara"));  // -> 166

  SecuredLinkedListMapElement<String, String> stringMapCopy[stringMap.size()];
  SecuredLinkedListMapElement<String, int> intMapCopy[intMap->size()];
  stringMap.getAll(stringMapCopy);
  intMap->getAll(intMapCopy);
  for (int i = 0; i < stringMap.size(); ++i) {
    Serial.println(stringMapCopy[i].key + "," + stringMapCopy[i].value + "," + intMapCopy[i].value);
  }
  // OUTPUT
  /*
  Sarah,Femal,161
  Alex,Male,190
  Dilara,Femal,166
  */
  
  stringMap.clear();
  intMap->clear();
  // stringMap = {}
  // intMap = {}
  Serial.println(stringMap.size()); // -> 0
  Serial.println(intMap->size());   // -> 0
}

void loop() {}
