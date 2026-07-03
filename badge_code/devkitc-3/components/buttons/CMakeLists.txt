set(srcs)
set(include_dirs "include")



list(APPEND srcs "buttons.c") 



idf_component_register(SRCS "${srcs}"
                       INCLUDE_DIRS "${include_dirs}"
                       PRIV_REQUIRES board
                                     esp32_hal
                                     esp_driver_gptimer) 
# PRIV_REQUIRES tells espidf the component dependancies of this component