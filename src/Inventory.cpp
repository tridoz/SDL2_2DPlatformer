#include "Inventory.h"

#include <iostream>
#include <ostream>

Inventory::Inventory() {
    for ( size_t i = 0 ; i<this->max_equipable_spells ; i++) {
        
    }
}



void Inventory::load(SDL_Renderer* renderer) {
    std::string spells_path = "../Assets/Spells/Spells_Data.xml";
    pugi::xml_document doc;

    if ( !doc.load_file(spells_path.c_str()) ) {
        std::cerr << "Failed to load spells xml file " << spells_path << std::endl;
        return;
    }else {
        std::cout << "Loaded spells xml file " << spells_path << std::endl;
    }

    pugi::xml_node root = doc.child("spells");

    if ( !root ) {
        std::cerr<<"Spells node not found "<<std::endl;
        return;
    }

    for ( pugi::xml_node item : root.children("type") ) {
        std::string spell_type = item.attribute("name").value();
    }



}



void Inventory::render_inventory(SDL_Renderer *renderer) {


}






