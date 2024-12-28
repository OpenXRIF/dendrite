use std::env;
use anyhow::{Error, Result};

fn main() -> Result<(), Error> {
    // TODO: This is starter code for the ROS2 node in rust using rclrs. Modify once prototype is finished and properly tested.
    let context = rclrs::Context::new(env::args())?;

    let node = rclrs::create_node(&context, "XRIF_Node")?;

    // infinite loop to keep the node alive
    while context.ok() 
    {
        println!("Node name: {:}", node.name());
        std::thread::sleep(std::time::Duration::from_millis(1500));
    }

    // Shutdown the ROS2 communication
    Ok(())
}
