pub mod mutex;
pub mod semaphore;

pub use mutex::{KMutex, KMutexGuard, Mutex, MutexGuard};
pub use semaphore::{KSemaphore, Semaphore};
