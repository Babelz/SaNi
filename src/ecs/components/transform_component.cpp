#include "sani/ecs/components/transform_component.hpp"
#include "sani/preprocessor/rtti_service.hpp"

namespace sani {

    void Transform::RTTI_Init() {
		auto& db = sani::rtti::TypeDatabase::getInstance();

        RTTI_REGISTER_TYPE(sani::Transform);
        RTTI_REGISTER_TYPE(sani::Transform*);

        RTTI_DEFAULT_CTOR(sani::Transform);
        
		RTTI_PUBLIC_FIELD(sani::Transform, position, sani::math::Vec3f);
        RTTI_PUBLIC_FIELD(sani::Transform, scale, sani::math::Vec2f);
        RTTI_PUBLIC_FIELD(sani::Transform, rotation, float32);

       /* RTTI_PUBLIC_FIELD_PTR(sani::Transform, position, sani::math::Vec3f);
        RTTI_PUBLIC_FIELD_PTR(sani::Transform, scale, sani::math::Vec2f);
        RTTI_PUBLIC_FIELD_PTR(sani::Transform, rotation, float32);*/

        db.types[typeof(sani::Transform*).getID()].addField<sani::Transform*, sani::math::Vec3f>("position",
            [](const sani::rtti::Object& instance) {                                        
            return instance.getValue<sani::Transform>().position;                              
            },                                                                               
	        [](sani::rtti::Object& instance, const sani::rtti::Object& v) {                  
                sani::Transform* tx = instance.getValue<sani::Transform*>();
                tx->position = v.getValue<sani::math::Vec3f>();              
        });     

        //RTTI_DEFAULT_SERVICE_CTOR(sani::Transform);
        db.types[typeof(sani::Transform*).getID()].                                                                       
            addServiceConstructor<sani::Transform*, se::SaNiEngine*, se::messages::DocumentMessage*>([](sani::rtti::Arguments& a){
            auto engine = a[0].getValue<sani::engine::SaNiEngine*>();                                           
            auto msg = a[1].getValue<sani::engine::messages::DocumentMessage*>();                               
            engine->routeMessage(msg);                                                                         
            sani::rtti::Object obj(static_cast<sani::Transform*>(msg->getData()));
            engine->releaseMessage(msg);                                                                       
            return obj;                                                                                        
        });

    }
}

