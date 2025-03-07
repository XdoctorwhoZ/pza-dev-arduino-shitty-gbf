///
use panduza_platform_core::Producer;

#[cfg(feature = "plugin")]
panduza_platform_core::plugin_interface!("arduino-shitty-gbf", "0.1.0");

//
// Import modules
mod arduino_shitty_gbf;


//
// Export the producers of the plugin
pub fn plugin_producers() -> Vec<Box<dyn Producer>> {
    let mut producers: Vec<Box<dyn Producer>> = vec![];
    producers.push(arduino_shitty_gbf::Package::default().boxed());

    return producers;
}
    