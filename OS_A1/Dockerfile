# Use an official Ubuntu runtime as the base image
FROM ubuntu:latest

# Set the working directory in the container
WORKDIR /app

# Copy the shell scripts into the container
COPY menu.sh get_processor_info.sh create_testing_directory.sh safe_delete.sh minedit /app/

# Make all shell scripts executable
RUN chmod +x menu.sh get_processor_info.sh create_testing_directory.sh safe_delete.sh minedit

# Install any required dependencies
# (No dependencies are required for this example)

# Define the default command to execute when the container starts
CMD ["/app/menu.sh"]

