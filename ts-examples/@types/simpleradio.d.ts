declare module "simpleradio" {
    type PacketDataType = "number" | "string" | "keyvalue";
    interface PacketInfo {
        group: number;
        address: string;
        rssi: number;
    }

    /**
     * Initialize the radio.
     * @param group The radio group to use.
     */
    function begin(group: number): void;

    /**
     * Set the radio group.
     * @param group The radio group to use.
     */
    function setGroup(group: number): void;

    /**
     * Send a string.
     * @param str The string to send.
     */
    function sendString(str: string): void;

    /**
     * Send a number.
     * @param num The number to send.
     */
    function sendNumber(num: number): void;

    /**
     * Send a key-value pair.
     * @param key The key to send.
     * @param value The number to send.
     */
    function sendKeyValue(key: string, value: number): void;

    /**
     * Register a callback for a packet type.
     * @param type The packet type to register for.
     * @param callback The callback to register.
     */
    function on(type: "number", callback: (num: number, info: PacketInfo) => void): void;

    /**
     * Register a callback for a packet type.
     * @param type The packet type to register for.
     * @param callback The callback to register.
     */
    function on(type: "string", callback: (str: string, info: PacketInfo) => void): void;

    /**
     * Register a callback for a packet type.
     * @param type The packet type to register for.
     * @param callback The callback to register.
     */
    function on(type: "keyvalue", callback: (key: string, value: number, info: PacketInfo) => void): void;
}
