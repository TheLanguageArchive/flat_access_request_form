<?php
/**
 * Check whether to show link
 *
 * @return boolean
 */
function flat_access_request_form_is_form_available(AbstractObject $object) {

    if (true === flat_access_request_form_excluded_object($object)) {

        // object is excluded, don't show link
        return false;
    }

    if (false === flat_access_request_form_check_roles()) {

        // user is not allowed to see form
        return false;
    }

    $facets = flat_access_request_form_get_access_levels();
    if (in_array(AccessLevelFacet::FACET_BUCKET_RESTRICTED, $facets)) {
        return true;
    }

    if (in_array(AccessLevelFacet::FACET_BUCKET_ACADEMIC, $facets)) {
        return flat_access_request_form_is_user_academic();
    }

    return false;
}

/**
 * Get access levels
 *
 * @return array
 */
function flat_access_request_form_get_access_levels()
{
    module_load_include('inc', 'flat_access_level_display', 'includes/AccessLevelFacet');

    global $_islandora_solr_queryclass;
    if (null === $_islandora_solr_queryclass) {
        return [];
    }

    $facets = $_islandora_solr_queryclass->islandoraSolrResult;
    return array_keys($facets['facet_counts']['facet_fields'][AccessLevelFacet::FACET_FIELD]);
}

/**
 * Check whether user has an academic role
 *
 * @return boolean
 */
function flat_access_request_form_is_user_academic() {

    module_load_include('inc', 'flat_access_level_display', 'includes/AccessLevel');

    global $user;
    return in_array(AccessLevel::ROLE_ACADEMIC, $user->roles);
}
