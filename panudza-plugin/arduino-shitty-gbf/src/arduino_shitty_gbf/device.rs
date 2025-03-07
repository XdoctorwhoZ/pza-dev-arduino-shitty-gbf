//
pub use super::SpecializedInterface;
pub use super::BooleanAccessorIndex;
pub use super::StringAccessorIndex;

use async_trait::async_trait;
use panduza_platform_core::Error;
use panduza_platform_core::Actions;
use panduza_platform_core::Instance;
use panduza_platform_core::template;
use panduza_platform_core::Container;
use std::time::Duration;
use tokio::time::sleep;

use panduza_platform_core::interface::usb::UsbSettings;
use panduza_platform_core::interface::usb::UsbTmcInterface;

#[derive(Default)]
///
///
pub struct Device {}

impl Device {
    /// Constructor
    ///
    pub fn new() -> Self {
        Device {}
    }
}

#[async_trait]
impl Actions for Device {
    ///
    ///
    ///
    async fn mount(&mut self, instance: Instance) -> Result<(), Error> {
        //
        //
        let logger = instance.logger().clone();


        
        //
        //
        let interface = SpecializedInterface::new(base, logger.clone());
        
//
        //
        template::attribute::number::mount(
            instance.clone(),
            interface.clone(),
            NumberAccessorIndex::Duty cycle as usize,
            "duty cycle",
            "info",
        )
        .await?;
    //
        //
        template::attribute::number::mount(
            instance.clone(),
            interface.clone(),
            NumberAccessorIndex::Period as usize,
            "period",
            "info",
        )
        .await?;
    
        
        Ok(())
    }
    ///
    /// Easiest way to implement the reboot event
    ///
    async fn wait_reboot_event(&mut self, mut _device: Instance) {
        sleep(Duration::from_secs(5)).await;
    }
}
    