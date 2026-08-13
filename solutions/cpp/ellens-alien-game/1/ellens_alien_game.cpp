namespace targets {
// TODO: Insert the code for the alien class here
    class Alien {
        private:
            int health{3};
    
        public:
            int x_coordinate;
            int y_coordinate;
            Alien(int x, int y){
                x_coordinate = x;
                y_coordinate = y;
            }
            int get_health(){
                return health;
            }
            int hit(){
                if (health > 0){
                    return --health;
                }
                return true;
                
            }
            bool is_alive(){
                if (health <= 0){
                    return false;
                }
                return true;
            }
            int teleport(int new_x, int new_y){
                x_coordinate = new_x;
                y_coordinate = new_y;
                return true;
            }
            bool collision_detection(Alien obj){
                int x{obj.x_coordinate};
                int y{obj.y_coordinate};
                if (x_coordinate == x && y_coordinate == y){
                    return true;
                }
                return false;
            }
    };

}  // namespace targets
