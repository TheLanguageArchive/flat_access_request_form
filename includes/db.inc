<?php
/**
 * Get entity form
 *
 * @return array
 */
function flat_access_request_form_get_form() {
    return node_load(variable_get('flat_access_request_form_id'));
}

/**
 * Fetch whether user has no access
 *
 * @param AbstractObject $object
 *
 * @return boolean
 */
function flat_access_request_has_no_access($object = null) {

    if (null === $object) {
        return true;
    }

    global $user;

    $pid       = trim(str_replace('info:fedora/', '', $object->id));
    $list      = variable_get('flat_access_request_form_exclusion_list');
    $list      = explode("\n", $list);
    $exclusion = [];

    foreach ($list as $item) {
        $exclusion[] = trim(str_replace('info:fedora/', '', $item));
    }

    return false === in_array($pid, $exclusion);
}

/**
 * Fetching all available webforms
 *
 * @return array
 */
function flat_access_request_form_get_webforms() {

    $query = db_select('webform', 'w');
    $query->join('node', 'n', 'w.nid = n.nid');
    $query->fields('n', ['nid', 'title']);

    return $query->execute()->fetchAllAssoc('nid');
}
